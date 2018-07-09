//
//  Window.cpp
//  GeometryShader
//
//  Created by shenyuanluo on 2017/9/8.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Window.hpp"
#include "Shader.hpp"
#include <math.h>
#include "Texture.hpp"
#include "Transform.hpp"
#include "Camera.hpp"

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif


#define RELEASE 0


/* 定义全局摄像机 */
Camera g_camera(glm::vec3(0.0f, 0.0f, 3.0f));
/* 鼠标上一帧位置 x 坐标 */
GLfloat g_lastCursorX;
/* 鼠标上一帧位置 y 坐标 */
GLfloat g_lastCursorY;
/* 鼠标是否第一次捕获 */
GLboolean g_isFirstCaptureMouse;

/* 光源位置 */
glm::vec3 lightPos(0.75f, 0.45f, 1.0f);



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
    m_currFTime = 0.0f;
    m_lastFTime = 0.0f;
    m_dealFTime = 0.0f;
    
    g_lastCursorX         = width * 0.5f;
    g_lastCursorY         = height * 0.5f;
    g_isFirstCaptureMouse = GL_TRUE;
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
void Window::render()
{
    // 顶点数据
    GLfloat points[] =
    {
        // 位置        颜色
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 左上
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 右上
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 右下
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, // 左下
    };;
    // 点 VAO
    GLuint pointVAO, pointVBO;
    glGenVertexArrays(1, &pointVAO);
    glGenBuffers(1, &pointVBO);
    glBindVertexArray(pointVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);
    
    // 画直线着色器
//    Shader houseShader(fullPath("PointsVS.glsl").c_str(), fullPath("PointsGS.glsl").c_str(), fullPath("PointsFS.glsl").c_str());
    
    // 画三角形着色器
    Shader houseShader(fullPath("PointsVS.glsl").c_str(), fullPath("TriangleGS.glsl").c_str(), fullPath("PointsFS.glsl").c_str());
    
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    while (!glfwWindowShouldClose(m_window))
    {
        /* 计算时间 */
        m_currFTime = glfwGetTime();
        if (0 == m_lastFTime)
        {
            m_lastFTime = m_currFTime;
        }
        m_dealFTime = m_currFTime - m_lastFTime;
        m_lastFTime = m_currFTime;
        
        /* 处理用户输入（鼠标、键盘。。）*/
        processInput(m_window);
        
        /* 设置清除缓存时窗体背景颜色 */
        glClearColor(0.2, 0.3, 0.3, 1.0f);
        /* 开始清除（颜色和深度缓冲） */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        houseShader.use();
        glBindVertexArray(pointVAO);
        glDrawArrays(GL_POINTS, 0, 4);
        
        /* 交换缓存 */
        glfwSwapBuffers(m_window);
        
        /* 检出是否有事件（键盘输入、鼠标移动）更新窗体状态 */
        glfwPollEvents();
    }
    /* 释放对象 */
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
    
    /* 隐藏鼠标光标 */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    /* 注册鼠标（移动）事件回调函数 */
    glfwSetCursorPosCallback(window, mouseMoveCB);
    /* 注册鼠标（滚动）事件回调函数 */
    glfwSetScrollCallback(window, mouseScrollCB);
    
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
    
    /* 判断用户是否按下 ‘W’ 按键，如果是，则向后移动 */
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W))
    {
        g_camera.keyboardMove(Move_forward, m_dealFTime);
    }
    /* 判断用户是否按下 ‘S’ 按键，如果是，则向前移动  */
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S))
    {
        g_camera.keyboardMove(Move_backward, m_dealFTime);
    }
    /* 判断用户是否按下 ‘A’ 按键，如果是，则向左移动  */
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))
    {
        g_camera.keyboardMove(Move_left, m_dealFTime);
    }
    /* 判断用户是否按下 ‘D’ 按键，如果是，则向右移动  */
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))
    {
        g_camera.keyboardMove(Move_right, m_dealFTime);
    }
    /* 判断用户是否按下 ‘↑’ 按键，如果是，则向上移动  */
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_UP))
    {
        g_camera.keyboardMove(Move_up, m_dealFTime);
    }
    /* 判断用户是否按下 ‘↓’ 按键，如果是，则向下移动  */
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_DOWN))
    {
        g_camera.keyboardMove(Move_down, m_dealFTime);
    }
}

#pragma mark -- 清理窗体
void Window::clearWindow()
{
    glfwTerminate();
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

#pragma mark -- 鼠标（移动）事件回调
void Window::mouseMoveCB(GLFWwindow* window, GLdouble posX, GLdouble posY)
{
    if (NULL == window)
    {
        std::cout << "无法处理鼠标（移动）事件， window = NULL !" << std::endl;
        return;
    }
    if(g_isFirstCaptureMouse)
    {
        g_lastCursorX = posX;
        g_lastCursorY = posY;
        g_isFirstCaptureMouse  = GL_FALSE;
    }
    GLfloat offsetX = posX - g_lastCursorX;
    GLfloat offsetY = g_lastCursorY - posY;   /* 注意这里是相反的，因为y坐标是从底部往顶部依次增大的 */
    g_lastCursorX     = posX;
    g_lastCursorY     = posY;
    
    g_camera.mouseMove(offsetX, offsetY);
}

#pragma mark -- 鼠标（滚动）事件回调
void Window::mouseScrollCB(GLFWwindow* window, GLdouble offsetX, GLdouble offsetY)
{
    if (NULL == window)
    {
        std::cout << "无法处理鼠标（滚动）事件， window = NULL !" << std::endl;
        return;
    }
    g_camera.mouseScroll(offsetY);
}

