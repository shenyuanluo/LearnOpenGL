//
//  Window.cpp
//  Camera_Ex01
//
//  Created by shenyuanluo on 2017/8/16.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Window.hpp"
#include "Shader.hpp"
#include <math.h>
#include "Texture.hpp"
#include "Transform.hpp"
#include "Camera.hpp"


/* 定义全局摄像机 */
Camera g_camera(glm::vec3(0.0f, 0.0f, 3.0f));
/* 鼠标上一帧位置 x 坐标 */
GLfloat g_lastCursorX;
/* 鼠标上一帧位置 y 坐标 */
GLfloat g_lastCursorY;
/* 鼠标是否第一次捕获 */
GLboolean g_isFirstCaptureMouse;



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

#pragma mark -- 渲染
void Window::render(GLfloat* vertexBuff, GLuint buffLen)
{
    if (NULL == vertexBuff || 0 == buffLen)
    {
        std::cout << "渲染失败！" << std::endl;
        return;
    }
    /* 设置顶点 */
    GLuint VAO = createVAO();
    GLuint VBO = createVBO(vertexBuff, buffLen);
    
    /* 创建着色器 对象 */
    Shader shader("vs.glsl", "fs.glsl");
    
    /* 指定 Uniform ‘texture1’ 为纹理单元：0（GL_TEXTURE0） */
    shader.setUniformInt1("texture1", 0);
    /* 指定 Uniform ‘texture2’ 为纹理单元：1（GL_TEXTURE1） */
    shader.setUniformInt1("texture2", 1);
    
    /* 创建纹理 对象1 */
    Texture texture1("container.jpg", GL_RGB, GL_RGB);
    /* 创建纹理 对象2 */
    Texture texture2("awesomeface.png", GL_RGBA, GL_RGBA);
    
    /* 立方体位置向量 */
    glm::vec3 cubePositions[] =
    {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    /* 设置开启‘深度测试’（默认是关闭的） */
    glEnable(GL_DEPTH_TEST);
    
    while (!glfwWindowShouldClose(m_window))
    {
        /* 处理用户输入（鼠标、键盘。。）*/
        processInput(m_window);
        
        /* 设置清除缓存时窗体背景颜色 */
        glClearColor(0.2, 0.3, 0.3, 1.0f);
        /* 开始清除（颜色和深度缓冲） */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        /* 使用着色器之前先激活 */
        shader.use();
        
        /* 在使用纹理之前先激活对应的纹理单元 */
        glActiveTexture(GL_TEXTURE0);
        /* 使用纹理 */
        texture1.use();
        
        /* 在使用纹理之前先激活对应的纹理单元 */
        glActiveTexture(GL_TEXTURE1);
        /* 使用纹理 */
        texture2.use();
        
        /* 计算时间 */
        m_currFTime = glfwGetTime();
        if (0 == m_lastFTime)
        {
            m_lastFTime = m_currFTime;
        }
        m_dealFTime = m_currFTime - m_lastFTime;
        m_lastFTime = m_currFTime;
        
        /* 渲染 10 个立方体 */
        for(GLuint i = 0; i < 10; i++)
        {
            /* 设置模型矩阵：使立方体位于不同位置且呈不同形态 */
            Transform modelM;
            modelM.translate(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
            GLfloat angle = 20.0f * i;
            modelM.rotate(modelM.radianWithDegree(angle), cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
            shader.setUniformMat4("modelMat", modelM.use());
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        /* 变换 */
        /* 设置模型矩阵 */
        Transform modelMat;
        shader.setUniformMat4("modelMat", modelMat.use());
        
        /* 用摄像机设置观察矩阵 */
        shader.setUniformMat4("viewMat", g_camera.use());
        
        /* 设置投影矩阵 */
        Transform projectionMat;
        projectionMat.perspective(g_camera.fov(), (GLfloat)m_width, (GLfloat)m_height, 0.1, 100.0f);
        shader.setUniformMat4("projectionMat", projectionMat.use());
        
        
        /* 绑定相应的顶点数组对象 */
        glBindVertexArray(VAO);
        /* 开始绘制 */
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        
        /* 交换缓存 */
        glfwSwapBuffers(m_window);
        
        /* 检出是否有事件（键盘输入、鼠标移动）更新窗体状态 */
        glfwPollEvents();
    }
    /* 释放对象 */
    glDeleteBuffers(1, &VBO);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    /* 启用顶点属性 */
    glEnableVertexAttribArray(0);
    
    /* 设置纹理属性 （告诉 OpenGL 如何解释使用纹理数据） */
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    /* 启用纹理属性 */
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
