//
//  main.cpp
//  HelloTriangleExercise1
//
//  Created by shenyuanluo on 2017/8/21.
//  Copyright © 2017年 shenyuanluo. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 声明 窗体大小改变回调函数指针
void frame_buffer_size_callback(GLFWwindow *window, GLint width, GLint height);

// 声明 处理用户输入回调函数指针
void processInput(GLFWwindow *window);

// 定义窗体大小
const GLuint windowWidth  = 800;
const GLuint windowHeight = 600;

// ---------------------- 创建顶点着色器 GLSL 源码 ----------------------
const GLchar *vertexShaderSouce = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// ---------------------- 创建片段着色器 GLSL 源码 ----------------------
const GLchar *fragmentShaderSouce = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "void main()\n"
    "{\n"
    "   fragColor = vec4(0.7f, 0.5f, 0.6f, 1.0f);\n"
    "}\0";


int main()
{
    // 初始化 GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      // 指定使用的 OpenGL 主版本号为 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);      // 指定使用的 OpenGL 子版本号为 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 指定 OpenGL 为 Core-profile 模式
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);    // 指定 OpenGL 是否向前兼容
#endif
    
    // 创建窗体
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Hello Triangle Exercise1", NULL, NULL);
    if (NULL == window)
    {
        std::cout << "创建窗体失败！" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);     // 设置 GLFW 上下文
    glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback); // 注册窗体大小改变回调
    
    // 调用 OpenGL API 之前先初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD 初始化失败！" << std::endl;
        return -1;
    }
    
    
    // ---------------------- 创建顶点着色器 ----------------------
    GLuint vertexShaderId;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSouce, NULL);    // 设置 GLSL 源码
    glCompileShader(vertexShaderId);    // 编译 GLSL 源码
    // 判断 GLSL 源码是否出错
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success)   // 编译出错
    {
        // 获取编译信息
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "错误：：顶点着色器：：编译失败\n" << infoLog << std::endl;
    }
    
    
    // ---------------------- 创建片段着色器 ----------------------
    GLuint fragmentShaderId;
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);          // 创建片段着色器引用 ID
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSouce, NULL);    // 设置 GLSL 源码
    glCompileShader(fragmentShaderId);    // 编译 GLSL 源码
    // 判断 GLSL 源码是否出错
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success)   // 编译出错
    {
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
        std::cout << "错误：：片段着色器：：编译失败\n" << infoLog << std::endl;
    }
    
    
    // ---------------------- 创建着色器程序 ----------------------
    GLuint shaderProgramId;
    shaderProgramId = glCreateProgram();    // 创建着色器程序
    glAttachShader(shaderProgramId, vertexShaderId);    // 添加顶点着色器
    glAttachShader(shaderProgramId, fragmentShaderId);    // 添加片段着色器
    glLinkProgram(shaderProgramId);     // 链接 着色器程序
    // 判断链接着色器程序是否出错
    glGetProgramiv(shaderProgramId, GL_COMPILE_STATUS, &success);
    if (!success)   // 链接出错
    {
        glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);   // 获取链接信息
        std::cout << "错误：：着色器程序：：链接失败\n" << infoLog << std::endl;
    }
    
    // 链接着色器成功后，释放着色器
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    
    
    // ---------------------- 画三角形 ----------------------
    
    /*                          /\      /\
                               /  \    /  \
                              / A  \  / B  \
                             /      \/      \
                             ----------------
     */
    GLfloat vertices[] =
    {
        -0.5f, -0.5f, 0.0f,         // 第一个三角形：左下顶点
         0.0f, -0.5f, 0.0f,         // 第一个三角形：右下顶点
       -0.25f,  0.25f, 0.0f,         // 第一个三角形：上顶点
         0.0f, -0.5f, 0.0f,         // 第二个三角形：左下顶点
         0.5f, -0.5f, 0.0f,         // 第二个三角形：右下顶点
        0.25f,  0.25f, 0.0f,         // 第二个三角形：上顶点
    };
    
    // 声明 顶点缓冲对象
    GLuint vertexBufferObject;
    GLuint vertexArrayObject;
    
    glGenVertexArrays(1, &vertexArrayObject);   // 创建顶点数组对象
    glGenBuffers(1, &vertexBufferObject);       // 创建 顶点缓冲
    
    glBindVertexArray(vertexArrayObject);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);  // 绑定顶点缓冲
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // 拷贝顶点数据到缓存中
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);    // 设置顶点属性
    glEnableVertexAttribArray(0);   // 启动顶点属性
    
    // 由于已经设置了顶点属性，顶点缓冲对象、顶点数组对象已作为顶点属性的顶点缓冲对象和顶点数组对象，所有可以把顶点缓冲对象和顶点数组对象进行解绑(但对于多个一般不解绑)
    glBindBuffer(GL_ARRAY_BUFFER, 0);   // 0 表示解绑，回收顶点缓冲对象资源
    glBindVertexArray(0);
    
    
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
        glBindVertexArray(vertexArrayObject);   // 最好试用期调用一次
        
        // 开始画图
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glfwSwapBuffers(window);    // 交换缓存
        glfwPollEvents();   // 检查是否有事件（键盘输入或鼠标移动）更新窗体状态
        
    }
    
    // 释放对象
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    
    // 退出 GLFW
    glfwTerminate();
    
    
    return 0;
}


// 监控窗体大小变化
void frame_buffer_size_callback(GLFWwindow *winddow, GLint width, GLint height)
{
    glViewport(0, 0, width, height);    // 设置窗体渲染大小
}


// 处理用户输入 回调
void processInput(GLFWwindow *window)
{
    // 判断用户是否按 ‘esc’ 按键，是则关闭窗体
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);    // 关闭窗体
    }
}

