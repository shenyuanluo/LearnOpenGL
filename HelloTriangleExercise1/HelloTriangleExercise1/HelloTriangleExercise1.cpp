//
//  HelloTriangleExercise1.c
//  HelloTriangleExercise1
//
//  Created by shenyuanluo on 2017/9/4.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "HelloTriangleExercise1.h"


// 日志缓冲大小
#define LOG_BUFF_LEN 512


#pragma mark - 常量声明
// 大小
const GLuint windowWidth  = 800;
const GLuint windowHeight = 600;

// 标题
const GLchar *windowTitle = "Hello Triangle";

// ---------------------- 创建顶点着色器 GLSL 源码 ----------------------
const GLchar *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n\0";

// ---------------------- 创建片段着色器 GLSL 源码 ----------------------
const GLchar *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.7f, 0.5f, 0.6f, 1.0f);\n"
    "}\n\0";

#pragma mark - 内部函数声明

/**
 GLFW window 大小改变回调

 @param window 窗体实例
 @param width 窗体宽度
 @param height 窗体高度
 */
void framebufferSizeCallback(GLFWwindow *window, GLint width, GLint height);


/**
 处理用户输入

 @param window 窗体实力
 */
void processInput(GLFWwindow *window);


/**
 创建顶点着色器
 
 @param shaderSource 创建着色器的 'GLSL'源码
 @return 成功，则返回顶点着色器对象 ID；失败，则返回 0
 */
GLuint vertexShader(const GLchar *shaderSource);


/**
 创建片段着色器
 
 @param shaderSource 创建着色器的 'GLSL'源码
 @return 成功，则返回片段着色器对象 ID；失败，则返回 0
 */
GLuint fragmentShader(const GLchar *shaderSource);


/**
 创建化着色器程序
 
 @return 成功，则返回着色器程序对象 ID；失败，则返回 0
 */
GLuint shaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId);


/**
 创建顶点缓冲对象
 
 @param vertexBuff 顶点数组缓冲
 @param buffLen 顶点数组长度
 @return 成功，则返回顶点缓冲对象 ID；失败，则返回 0
 */
GLuint vertexBufferObj(GLfloat *vertexBuff, GLint buffLen);


/**
 创建索引缓冲对象

 @param indicesBuff 顶点数组缓冲
 @param buffLen 顶点数组长度
 @return 成功，则返回索引缓冲对象 ID；失败，则返回 0
 */
GLuint elementBufferObj(GLuint *indicesBuff, GLint buffLen);


/**
 创建顶点数组对象
 
 @return 成功，则返回顶点数组对象 ID；失败，则返回 0
 */
GLuint vertexArrayObj();


#pragma mark - 外部函数实现
#pragma mark -- 初始化窗体
GLFWwindow * initWindow()
{
    // 初始化 GLFW
    if (!glfwInit())
    {
        std::cout << "Init GLFW failure !" << std::endl;
        return NULL;
    }
    // 告诉 GLFW 使用的 OpenGL 版本为：3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 使用 OpenGL 的 Core-profile 模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__ // macOS 系统表示
    // 指定 OpenGL 上下文需向前兼容
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // 创建 GLFWWindow 对象
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
    if (NULL == window)
    {
        std::cout << "Create window failure ！" << std::endl;
        // 退出 GLFW
        glfwTerminate();
        return NULL;
    }
    // 通知 GLFW 将窗体的上下文设置为当前线程的上下文
    glfwMakeContextCurrent(window);
    // 注册 GLFW widow 大小改变的回调函数
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    return  window;
}


#pragma mark -- 初始化 GLAD
RetStatus initGlad()
{
    // GLAD 是用来管理 OpenGL 的函数指针的，所以在调用任何 OpenGL 的 API 之前先需要初始化 GLAD 。（GLFW 给我们的是 glfwGetProcAddress， 它根据我们编译的系统定义正确的函数。）
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Init GLAD failure ！" << std::endl;
        return RetError;
    }
    return RetSuccess;
}


#pragma mark -- 创建着色器程序
GLuint shaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
{
    if (0 >= vertexShaderId || 0 >= fragmentShaderId)
    {
        std::cout << "Cann't create Shader Program withdout vertexShader or fragmentShader !" << std::endl;
        return 0;
    }
    // -------------------------- 着色器程序 --------------------------
    // 声明一个引用 着色器程序对象 ID
    GLuint shaderProgramId;
    // 创建着色器程序对象
    shaderProgramId = glCreateProgram();
    // 附加 顶点着色去
    glAttachShader(shaderProgramId, vertexShaderId);
    // 附加片段合作社区
    glAttachShader(shaderProgramId, fragmentShaderId);
    // 链接 着色器程序
    glLinkProgram(shaderProgramId);
    
    // 检查 着色器程序是否链接出错
    GLint success;
    GLchar infoLog[LOG_BUFF_LEN];
    glGetProgramiv(shaderProgramId, GL_COMPILE_STATUS, &success);
    if (!success)  // 如果链接失败
    {
        // 获取链接信息
        glGetProgramInfoLog(shaderProgramId, LOG_BUFF_LEN, NULL, infoLog);
        std::cout << "Create shader program failure !" << infoLog << std::endl;
        return 0;
    }
    
    // 链接 着色器成功之后，可以释放 着色器对象
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    
    return  shaderProgramId;
}


void render(GLFWwindow *window, GLfloat *vertexBuff, GLint buffLen)
{
    if (NULL == window
        || NULL == vertexBuff || 0 >= buffLen)
    {
        std::cout << "Render failure !" << std::endl;
        return ;
    }
    GLuint vertexShaderId   = vertexShader(vertexShaderSource);
    GLuint fragmentShaderId = fragmentShader(fragmentShaderSource);
    GLuint shaderProgramId  = shaderProgram(vertexShaderId, fragmentShaderId);
    if (0 == vertexShaderId
        || 0 == fragmentShaderId
        || 0 == shaderProgramId)
    {
        return ;
    }
    glUseProgram(shaderProgramId);
    
    GLuint VAO = vertexArrayObj();
    
    GLuint VBO = vertexBufferObj(vertexBuff, buffLen);
    
    // 画线框
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // 循环渲染
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 设置颜色
        glClear(GL_COLOR_BUFFER_BIT);           // 应用颜色
        
        // 激活着色器程序
        glUseProgram(shaderProgramId);
        glBindVertexArray(VAO);   // 最好试用期调用一次
        
        // 开始画图
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwSwapBuffers(window);    // 交换缓存
        glfwPollEvents();   // 检查是否有事件（键盘输入或鼠标移动）更新窗体状态
    }
    
    // 释放对象
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


#pragma mark - 内部函数实现
#pragma mark -- 处理 GLFW window 大小改变回调
void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    if (NULL == window)
    {
        std::cout << "Window is NULL, can not change window's size !" << std::endl;
        return ;
    }
    // 告诉 OpenGL 渲染窗口的位置、大小（确保渲染大小跟窗体大小一致，也可用比窗体小，在视网膜显示屏时甚至比窗体大）
    glViewport(0, 0, width, height);
}


#pragma mark -- 处理用户输入 回调
void processInput(GLFWwindow *window)
{
    if (NULL == window)
    {
        std::cout << "Window is NULL, can not process window inputs !" << std::endl;
        return ;
    }
    // 判断用户是否按 ‘esc’ 按键，是则关闭窗体
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        // 关闭窗体
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


#pragma mark -- 创建顶点着色器
GLuint vertexShader(const GLchar *shaderSource)
{
    if (NULL == shaderSource)
    {
        std::cout << "ShaderSource is NULL, can not create vertex shader !" << std::endl;
        return 0;
    }
    // 创建并编译 着色器程序
    // -------------------------- 顶点着色器 --------------------------
    // 声明一个引用 顶点着色器对象 ID
    GLuint vertexShaderId;
    // 创建 着色器（指明是顶点着色器）
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    // 执行创建顶点着色器 GLSL 的源码
    glShaderSource(vertexShaderId, 1, &shaderSource, NULL);
    // 编译 GLSL 源码
    glCompileShader(vertexShaderId);
    
    // 检查 GLSL 源码是否有错误
    GLint success;
    GLchar infoLog[LOG_BUFF_LEN];
    // 检查编译 GLSL 是否出错
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)   // 如果编译失败
    {
        // 获取编译信息
        glGetShaderInfoLog(vertexShaderId, LOG_BUFF_LEN, NULL, infoLog);
        std::cout<< "Create vertex shader failure !" << infoLog << std::endl;
        
        return 0;
    }
    return vertexShaderId;
}


#pragma mark -- 创建片段着色器
GLuint fragmentShader(const GLchar *shaderSource)
{
    if (NULL == shaderSource)
    {
        std::cout << "ShaderSource is NULL, can not create fragment shader !" << std::endl;
        return 0;
    }
    // -------------------------- 片段着色器 --------------------------
    // 声明一个引用 片段着色器对象 ID
    GLuint fragmentShaderId;
    // 创建 着色器（指明是片段着色器）
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    // 执行创建片段着色器 GLSL 的源码
    glShaderSource(fragmentShaderId, 1, &shaderSource, NULL);
    // 编译 GLSL 源码
    glCompileShader(fragmentShaderId);
    
    GLint success;
    GLchar infoLog[LOG_BUFF_LEN];
    // 检查编译 GLSL 是否出错
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success) // 如果编译失败
    {
        // 获取编译信息
        glGetShaderInfoLog(fragmentShaderId, LOG_BUFF_LEN, NULL, infoLog);
        std::cout << "Create fragment shader failure !" << infoLog << std::endl;
        
        return 0;
    }
    return fragmentShaderId;
}


#pragma mark -- 创建顶点缓冲对象
GLuint vertexBufferObj(GLfloat *vertexBuff, GLint buffLen)
{
    if (NULL == vertexBuff || 0 >= buffLen)
    {
        std::cout << "VertexBuff is NULL, can not create Vertex Buffer Object !" << std::endl;
        return 0;
    }
    // 声明一个引用 顶点缓存对象 ID
    GLuint VBO  /* 顶点缓冲对象（Vertex Buffer Object） */;
    
    // 生成一个 顶点缓存对象
    glGenBuffers(1, &VBO);
    
    // 绑定顶点缓存对象类型
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 拷贝顶点数据到顶点缓存对象ID引用的缓存中
    glBufferData(GL_ARRAY_BUFFER, buffLen, vertexBuff, GL_STATIC_DRAW);
    // 设置顶点属性 （告诉 OpenGL 如何解释使用顶点数据）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    // 启动顶点属性
    glEnableVertexAttribArray(0);
    
    return VBO;
}


#pragma mark -- 创建索引缓冲对象
GLuint elementBufferObj(GLuint *indexBuff, GLint buffLen)
{
    if (NULL == indexBuff || 0 >= buffLen)
    {
        std::cout << "IndexBuff is NULL, can not create Element Buffer Object !" << std::endl;
        return 0;
    }
    // 声明一个引用 索引缓存对象 ID
    GLuint EBO  /* 索引缓冲对象（Element Buffer Object） */;
    // 生成一个 索引缓存对象
    glGenBuffers(1, &EBO);
    
    // 绑定 索引缓存对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 拷贝 索引数据到索引缓存对象 ID 引用的缓存中
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffLen, indexBuff, GL_STATIC_DRAW);
    
    return EBO;
}


#pragma mark -- 创建顶点数组对象
GLuint vertexArrayObj()
{
    // 声明一个引用 顶点数组对象 ID
    GLuint VAO  /* 顶点数组对象（Vertex Array Object） */;
    // 生成一个顶点数组对象(可包含：VBO，EBO，VertexAttribPointer )
    glGenVertexArrays(1, &VAO);
    
    // 绑定顶点数组对象在先，然后再绑定和设置顶点缓存对象，并且配置顶点属性
    // 绑定顶点数组对象
    glBindVertexArray(VAO);
    
    return VAO;
}


