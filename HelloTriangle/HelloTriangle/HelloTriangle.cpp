//
//  HelloTriangle.cpp
//  HelloTriangle
//
//  Created by shenyuanluo on 2017/9/1.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "HelloTriangle.h"


// 日志缓冲大小
#define LOG_BUFF_LEN 512


#pragma mark - 常量声明
// 大小
const GLuint windowWidth  = 800;
const GLuint windowHeight = 600;

// 标题
const GLchar *windowTitle = "Hello Triangle";

// GLSL 创建 顶点着色器源码
const GLchar *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
// GLSL 创建 片段着色器源码
const GLchar *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.7f, 0.5f, 0.6f, 1.0f);\n"
    "}\0";

#pragma mark - 内部函数声明
#pragma mark -- 声明 GLFW window 大小改变回调
void framebuffer_size_callback(GLFWwindow *window, GLint width, GLint height);

#pragma mark -- 声明 处理用户输入
void processInput(GLFWwindow *window);

#pragma mark -- 创建顶点着色器
GLuint vertexShader();

#pragma mark -- 创建片段着色器
GLuint fragmentShader();

#pragma mark -- 创建顶点缓冲对象
GLuint vertexBufferObj(GLfloat *vertexBuff, GLint bufLen);

#pragma mark -- 创建索引缓冲对象
GLuint elementBufferObj(GLuint *indicesBuff, GLint buffLen);

#pragma mark -- 创建顶点数组对象
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
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
RetStatus initShaderProgram()
{
    GLuint vertexShaderId = vertexShader();
    if (0 == vertexShaderId)
    {
        return RetError;
    }
    GLuint fragmentShaderId = fragmentShader();
    if (0 == fragmentShaderId)
    {
        return RetError;
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
    }
    
    // 链接 着色器成功之后，可以释放 着色器对象
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    
    // 激活着色器程序
    glUseProgram(shaderProgramId);
    
    return  RetSuccess;
}


void render(GLFWwindow *window, GLfloat *vertexBuff, GLint buffLen)
{
    GLuint VAO = vertexArrayObj();
    
    GLuint VBO = vertexBufferObj(vertexBuff, buffLen);
    
    // 定义 索引缓存数据数据
    GLuint indices[] =
    {
        0, 1, 2,                        // 第一个三角形（左上三角形）
        1, 2, 3,                        // 第二个三角形（右下三角形）
    };
    GLuint EBO = elementBufferObj(indices, sizeof(indices));
    
    // 如果想画线框，去掉下面的注释
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 处理输入
        processInput(window);
        
        //渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 状态设置函数
        glClear(GL_COLOR_BUFFER_BIT);           // 状态使用函数
        
        // -------------------------- 开始画三角形 --------------------------
        //
        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
        
        // 交换缓存
        glfwSwapBuffers(window);
        // 检查是否有事件（键盘输入或鼠标移动）更新窗体状态
        glfwPollEvents();
    }
    
    // 释放对象
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


#pragma mark - 内部函数实现
#pragma mark -- 处理 GLFW window 大小改变回调
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // 告诉 OpenGL 渲染窗口的位置、大小（确保渲染大小跟窗体大小一致，也可用比窗体小，在视网膜显示屏时甚至比窗体大）
    glViewport(0, 0, width, height);
}


#pragma mark -- 处理用户输入 回调
void processInput(GLFWwindow *window)
{
    // 判断用户是否按 ‘esc’ 按键，是则关闭窗体
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        // 关闭窗体
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


#pragma mark -- 创建顶点着色器
GLuint vertexShader()
{
    // 创建并编译 着色器程序
    // -------------------------- 顶点着色器 --------------------------
    // 声明一个引用 顶点着色器对象 ID
    GLuint vertexShaderId;
    // 创建 着色器（指明是顶点着色器）
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    // 执行创建顶点着色器 GLSL 的源码
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
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
GLuint fragmentShader()
{
    // -------------------------- 片段着色器 --------------------------
    // 声明一个引用 片段着色器对象 ID
    GLuint fragmentShaderId;
    // 创建 着色器（指明是片段着色器）
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    // 执行创建片段着色器 GLSL 的源码
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
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
GLuint vertexBufferObj(GLfloat *vertexBuff, GLint bufLen)
{
    // 声明一个引用 顶点缓存对象 ID
    GLuint VBO  /* 顶点缓冲对象（Vertex Buffer Object） */;
    
    // 生成一个 顶点缓存对象
    glGenBuffers(1, &VBO);
    
    // 绑定顶点缓存对象类型
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 拷贝顶点数据到顶点缓存对象ID引用的缓存中
    glBufferData(GL_ARRAY_BUFFER, bufLen, vertexBuff, GL_STATIC_DRAW);
    // 设置顶点属性 （告诉 OpenGL 如何解释使用顶点数据）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    // 启动顶点属性
    glEnableVertexAttribArray(0);
    
    return VBO;
}


#pragma mark -- 创建索引缓冲对象
GLuint elementBufferObj(GLuint *indexBuff, GLint buffLen)
{
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


