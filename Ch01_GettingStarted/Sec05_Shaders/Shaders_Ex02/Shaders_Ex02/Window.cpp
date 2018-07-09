//
//  Window.cpp
//  Shaders_Ex02
//
//  Created by shenyuanluo on 2017/8/12.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Window.hpp"
#include "Shader.hpp"
#include <math.h>

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif


#define RELEASE 0


#pragma mark - public
#pragma mark -- 构造函数
Window::Window(GLuint width, GLuint height, const GLchar* title) : m_width(width), m_height(height), m_title(title)
{
    m_window = createWindow();
    if (NULL == m_window)
    {
        return;
    }
    if (Ret_failure == initGlad())
    {
        return;
    }
}

#pragma mark -- 析构函数
Window::~Window()
{
    clearWindow();
    m_window = NULL;
    m_title  = NULL;
}

#pragma mark -- 设置可执行文件所在目录
void Window::setCWD(const std::string &cwdPath)
{
    m_cwd = cwdPath.substr(0, cwdPath.find_last_of('/'));
}

#pragma mark -- 渲染
void Window::render(GLfloat* vertexBuff, GLuint buffLen)
{
    if (NULL == vertexBuff || 0 == buffLen)
    {
        std::cout << "渲染失败！" << std::endl;
        return;
    }
    GLuint indices[] =
    {
        0, 1, 2,
    };
    /* 设置顶点 */
    GLuint VAO = createVAO();
    GLuint VBO = createVBO(vertexBuff, buffLen);
    GLuint EBO = createEBO(indices, sizeof(indices));
    
    Shader shader(fullPath("vs.glsl").c_str(), fullPath("fs.glsl").c_str());
    
    shader.setUniformFloat("xOffset", 0.5f);
    
    /* 如果想画线框，去掉下面的注释 */
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while (!glfwWindowShouldClose(m_window))
    {
        /* 处理用户输入（鼠标、键盘。。）*/
        processInput(m_window);
        
        /* 设置清除缓存时窗体背景颜色 */
        glClearColor(0.2, 0.3, 0.3, 1.0f);
        /* 开始清除 */
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        /* 使用着色器之前先激活 */
        shader.use();
        /* 绑定相应的顶点数组对象 */
        glBindVertexArray(VAO);
        
        /* 开始绘制 */
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GLuint), GL_UNSIGNED_INT, (void *)0);
        
        
        /* 交换缓存 */
        glfwSwapBuffers(m_window);
        
        /* 检出是否有事件（键盘输入、鼠标移动）更新窗体状态 */
        glfwPollEvents();
    }
    /* 释放对象 */
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
    clearWindow();
}


#pragma mark - private
#pragma mark -- 创建窗体
GLFWwindow* Window::createWindow()
{
    /* 初始化 GLFW */
    if (!glfwInit())
    {
        std::cout << "GLFW 初始化失败 !" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    /* 告诉 GLFW 使用的 OpenGL 版本是 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    /* 告诉 GLFW 使用的是 Core-OpenGL 模式 */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* apple 兼容 */
#ifdef __APPLE__
    /* 指定 OpenGL 上下文需要向前兼容（如不指定，版本不匹配时会 crash ） */
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
    
    /* 创建 GLFWWindow 实例 */
    GLFWwindow *window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
    if (NULL == window)
    {
        std::cout << "创建窗体实例失败 ！" << std::endl;
        clearWindow();
        return NULL;
    }
    /* 通知 GLFW 将窗口的上下文设置为当前线程的主上下文 */
    glfwMakeContextCurrent(window);
    /* 注册 GLFW 窗体大小的回调函数 */
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCB);
    /* 注册 GLFW 错误回调 */
    glfwSetErrorCallback(errorCallback);
    
    
    return window;
}

#pragma mark -- 初始化 GLAD
RetStatus Window::initGlad()
{
    /*
     GLAD 是用来管理 OpenGL 的函数指针的，所以在调用任何 OpenGL 的
     函数之前先需要初始化GLAD。(GLFW 给我们的是glfwGetProcAddress，
     它根据我们编译的系统定义了正确的函数。)
     */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD 初始化失败 ！" << std::endl;
        clearWindow();
        return Ret_failure;
    }
    return Ret_success;
}

#pragma mark -- 获取文件的绝对路径
std::string Window::fullPath(const std::string &filePath)
{
    static int chdirCount = 0;
    std::string absolutePath = filePath;
#if RELEASE
    if (0 == chdirCount)
    {
        chdir(m_cwd.c_str());    // 切换到可执行文件目录
        chdir("..");    // 跳出’Products‘目录，返回上层目录
        chdirCount++;
    }
    char buffer[3 * 1024];
    char *answer = getcwd(buffer, sizeof(buffer));
    if (answer)
    {
        absolutePath = answer;
    }
    absolutePath = absolutePath + "/" + filePath;
#endif
    return absolutePath;
}

#pragma mark -- 处理用户输入事件
void Window::processInput(GLFWwindow* window)
{
    if (NULL == window)
    {
        std::cout << "无法处理用户输入， window = NULL !" << std::endl;
        return;
    }
    /* 判断用户是否按下 ‘esc’ 按键，如果是，则关闭窗体 */
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        /* 关闭窗体 */
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

#pragma mark -- 清理窗体
void Window::clearWindow()
{
    glfwTerminate();
}

#pragma mark -- 创建顶点数组对象（Vertex Array Object）
GLuint Window::createVAO()
{
    /* 声明一个引用 顶点数组对象 ID */
    GLuint vertexArrayObj;
    /* 创建一个顶点数组对象（可包含：VBO，EBO，VertexAttribPointer ） */
    glGenVertexArrays(1, &vertexArrayObj);
    /* 绑定顶点数组对象在先，然后再绑定和设置顶点缓存对象，并且配置顶点属性 */
    /* 绑定顶点数组对象 */
    glBindVertexArray(vertexArrayObj);
    
    return vertexArrayObj;
}

#pragma mark -- 创建顶点缓存对象）
GLuint Window::createVBO(GLfloat* vertexBuff, GLuint buffLen)
{
    if (NULL == vertexBuff || 0 == buffLen)
    {
        std::cout << "无法创建 VBO" << std::endl;
        return 0;
    }
    /* 声明一个引用 顶点缓存对象 ID */
    GLuint VBO; /* （Vertex Buffer Object */
    /* 创建顶点缓存对象*/
    glGenBuffers(1, &VBO);
    /* 绑定缓存对象类型为：顶点数组缓存 */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /* 拷贝顶点数据到顶点缓存对象ID引用的缓存中 */
    glBufferData(GL_ARRAY_BUFFER, buffLen, vertexBuff, GL_STATIC_DRAW);
    /* 设置顶点属性 （告诉 OpenGL 如何解释使用顶点数据） */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    /* 启用顶点属性 */
    glEnableVertexAttribArray(0);
    
    /* 设置颜色属性 （告诉 OpenGL 如何解释使用颜色数据） */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    /* 启用颜色属性 */
    glEnableVertexAttribArray(1);
    
    return VBO;
}

#pragma mark -- 创建索引缓存对象（Element Buffer Object）
GLuint Window::createEBO(GLuint* indicesBuff, GLuint buffLen)
{
    if (NULL == indicesBuff || 0 == buffLen)
    {
        std::cout << "无法创建 EVO !" << std::endl;
        return 0;
    }
    /* 声明一个引用 索引缓存对象 ID */
    GLuint EBO; /* （Element Buffer Object） */
    /* 创建 索引缓存对象 */
    glGenBuffers(1, &EBO);
    /* 绑定缓存对象类型为：索引数组缓存 */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    /* 拷贝索引数据到顶点缓存对象ID引用的缓存中 */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffLen, indicesBuff, GL_STATIC_DRAW);
    
    return EBO;
}


#pragma mark - 回调
#pragma mark -- 错误回调
void Window::errorCallback(GLint errorCode, const GLchar* description)
{
    std::cout << "【GLFW 错误回调】：errorCode = " << errorCode << ", description = " << description << std::endl;
}

#pragma mark -- 大小变化回调
void Window::frameBufferSizeCB(GLFWwindow* window, GLint width, GLint height)
{
    if (NULL == window)
    {
        std::cout << "无法改变窗体大小， window = NULL !" << std::endl;
        return;
    }
    /*
     告诉 OpenGL 渲染 GLFW 窗体的位置，大小（确保渲染大小跟窗体大小一致，
     也可用比窗体小，在视网膜显示屏时甚至比窗体大）
     */
    glViewport(0, 0, width, height);
}
