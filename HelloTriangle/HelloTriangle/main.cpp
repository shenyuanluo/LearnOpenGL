//
//  main.cpp
//  HelloTriangle
//
//  Created by shenyuanluo on 2017/8/13.
//  Copyright © 2017年 shenyuanluo. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// 声明 GLFW window 大小改变回调
void framebuffer_size_callback(GLFWwindow *window, GLint width, GLint height);

// 声明 处理用户输入
void processInput(GLFWwindow *window);

// 设置
const GLuint WINDOW_WIDTH  = 800;
const GLuint WINDOW_HEIGHT = 600;

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
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main()
{
    // 初始化 GLFW
    glfwInit();
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
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello Triangle", NULL, NULL);
    if (NULL == window)
    {
        std::cout << "创建 GLFW 窗体失败！" << std::endl;
        // 退出 GLFW
        glfwTerminate();
        return -1;
    }
    // 通知 GLFW 将窗体的上下文设置为当前线程的上下文
    glfwMakeContextCurrent(window);
    // 注册 GLFW widow 大小改变的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    
    // GLAD 是用来管理 OpenGL 的函数指针的，所以在调用任何 OpenGL 的 API 之前先需要初始化 GLAD 。（GLFW 给我们的是 glfwGetProcAddress， 它根据我们编译的系统定义正确的函数。）
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD 初始化失败！" << std::endl;
        return -1;
    }
    
    
    // 创建并编译 着色器程序
    // -------------------------- 顶点着色器 --------------------------
    // 声明一个引用 顶点着色器对象 ID
    GLuint vertexShader;
    // 创建 着色器（指明是顶点着色器）
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 执行创建顶点着色器 GLSL 的源码
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // 编译 GLSL 源码
    glCompileShader(vertexShader);
    
    // 检查 GLSL 源码是否有错误
    GLint success;
    GLchar infoLog[512];
    // 检查编译 GLSL 是否出错
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)   // 如果编译失败
    {
        // 获取编译信息
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout<< "错误::顶点着色器::编译失败！\n" << infoLog << std::endl;
    }
    
    
    // -------------------------- 片段着色器 --------------------------
    // 声明一个引用 片段着色器对象 ID
    GLuint fragmentShader;
    // 创建 着色器（指明是片段着色器）
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // 执行创建片段着色器 GLSL 的源码
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // 编译 GLSL 源码
    glCompileShader(fragmentShader);
    // 检查编译 GLSL 是否出错
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) // 如果编译失败
    {
        // 获取编译信息
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "错误::片段着色器::编译失败！\n" << infoLog << std::endl;
    }
    
    
    // -------------------------- 着色器程序 --------------------------
    // 声明一个引用 着色器程序对象 ID
    GLuint shaderProgram;
    // 创建着色器程序对象
    shaderProgram = glCreateProgram();
    // 附加 顶点着色去
    glAttachShader(shaderProgram, vertexShader);
    // 附加片段合作社区
    glAttachShader(shaderProgram, fragmentShader);
    // 链接 着色器程序
    glLinkProgram(shaderProgram);
    // 检查 着色器程序是否链接出错
    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success)  // 如果链接失败
    {
        // 获取链接信息
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "错误::着色器程序::链接失败！\n" << infoLog << std::endl;
    }
    
    // 链接 着色器成功之后，可以释放 着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // -------------------------- 画三角形 --------------------------
    //    // 定义 三角形顶点数据数组
    //    GLfloat vertices[] =
    //    {
    //        -0.5f, -0.5f, 0.0f,         // 左顶点
    //         0.5f, -0.5f, 0.0f,         // 右顶点
    //         0.0f,  0.5f, 0.0f          // 上顶点
    //    };
    
    // -------------------------- 画矩形 --------------------------
    // 定义 矩形顶点数据数组
    GLfloat vertices[] =
    {
        -0.5f,  0.5f, 0.0f,             // 左上角 顶点
        0.5f,  0.5f, 0.0f,             // 右上角 顶点
        0.5f, -0.5f, 0.0f,             // 右下角 顶点
        -0.5f, -0.5f, 0.0f,             // 左下角 顶点
    };
    // 定义 索引缓存数据数据
    GLuint indices[] =
    {
        0, 1, 2,                        // 第一个三角形（右上三角形）
        2, 3, 0,                        // 第二个三角形（左下三角形）
    };
    
    // 声明一个引用 顶点缓存对象 ID
    GLuint VBO  /* 顶点缓冲对象（Vertex Buffer Object） */;
    GLuint VAO  /* 顶点数组对象（Vertex Array Object） */;
    GLuint EBO  /* 索引缓冲对象（Element Buffer Object） */;
    // 生成一个顶点数组对象(可包含：VBO，EBO，VertexAttribPointer )
    glGenVertexArrays(1, &VAO);
    // 生成一个 定点缓存对象
    glGenBuffers(1, &VBO);
    // 生成一个 索引缓存对象
    glGenBuffers(1, &EBO);
    
    // 绑定顶点数组对象在先，然后再绑定和设置顶点缓存对象，并且配置顶点属性
    // 绑定顶点数组对象
    glBindVertexArray(VAO);
    
    // 绑定顶点缓存对象类型
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 拷贝顶点数据到顶点缓存对象ID引用的缓存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 绑定 索引缓存对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // 拷贝 索引数据到索引缓存对象 ID 引用的缓存中
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // 设置顶点属性 （告诉 OpenGL 如何解释使用顶点数据）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    // 启动顶点属性
    glEnableVertexAttribArray(0);
    
    // 使 VBO 绑定状态
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
    
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
        // 激活着色器程序
        glUseProgram(shaderProgram);
        //
        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // 交换缓存
        glfwSwapBuffers(window);
        // 检查是否有事件（键盘输入或鼠标移动）更新窗体状态
        glfwPollEvents();
    }
    
    // 释放对象
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    
    // 退出 GLFW
    glfwTerminate();
    
    return 0;
}



// 处理 GLFW window 大小改变回调
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // 告诉 OpenGL 渲染窗口的位置、大小（确保渲染大小跟窗体大小一致，也可用比窗体小，在视网膜显示屏时甚至比窗体大）
    glViewport(0, 0, width, height);
}


// 处理用户输入 回调
void processInput(GLFWwindow *window)
{
    // 判断用户是否按 ‘esc’ 按键，是则关闭窗体
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        // 关闭窗体
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
