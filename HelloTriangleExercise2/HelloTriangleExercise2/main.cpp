//
//  main.cpp
//  HelloTriangleExercise2
//
//  Created by shenyuanluo on 2017/8/25.
//  Copyright © 2017年 shenyuanluo. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const GLint windowWidth  = 800;
const GLint windowHeight = 600;

void framBufferSizeCallback(GLFWwindow *window, GLint width, GLint height);

void processInput(GLFWwindow *window);

const GLchar *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const GLchar *fragmentShaderSource = "#version 330 core\n"
    "out vec4 fragColor;\n"
    "void main()\n"
    "{\n"
    "   fragColor = vec4(0.5, 0.8, 0.3, 1.0);\n"
    "}\0";

int main ()
{
    // 初始化窗体
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
    
    // 创建窗体
    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Hello Triangle Exercise2", NULL, NULL);
    if (NULL == window)
    {
        std::cout << "创建窗体失败！" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // 设置上下文
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framBufferSizeCallback);
    
    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD 初始化失败！" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // 创建着色器
    GLuint vertexShaderId;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderId);
    
    GLint isSuccess;
    GLchar infoLog[512];
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &isSuccess);
    if (!isSuccess)
    {
        glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
        std::cout << "创建顶点着色器失败！" << infoLog << std::endl;
        glfwTerminate();
        return -1;
    }
    
    GLuint fragmentShaderId;
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &isSuccess);
    if (!isSuccess)
    {
        glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
        std::cout << "创建片段着色器失败！" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    GLuint shaderProgramId;
    shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &isSuccess);
    if (!isSuccess)
    {
        glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
        std::cout << "链接着色程序失败！" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // 删除着色器
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
    
    // 第一个三角形
    GLfloat triangle1[] =
    {
        -0.8f, -0.3f, 0.0f,         // 左下角顶点
        -0.2f, -0.3f, 0.0f,         // 右下角顶点
        -0.5f,  0.3f, 0.0f,         // 上顶点
    };
    
    // 第二个三角形
    GLfloat triangle2[] =
    {
         0.2f, -0.3f, 0.8f,         // 左下顶点
         0.8f, -0.3f, 0.0f,         // 右下顶点
         0.5f,  0.3f, 0.0f,         // 上顶点
    };
    
    GLuint vertexBufferObjs[2];
    GLuint vertexArrayObjs[2];
    
    // 创建顶点数组
    glGenVertexArrays(2, vertexArrayObjs);
    // 创建 顶点缓存
    glGenBuffers(2, vertexBufferObjs);

    // 绑定第一个顶点数组
    glBindVertexArray(vertexArrayObjs[0]);
    
    // 绑定第一个顶点缓冲
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);        // 第一个三角形数据拷贝
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);    // 设置第一个顶点数组的顶点属性
    
    // 启用第一个顶点属性数组
    glEnableVertexAttribArray(0);
    
    /* ---------- 绑定不同的缓冲数组时，不需要里面解绑 ---------- */
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
    
    // 绑定第二个顶点数组
    glBindVertexArray(vertexArrayObjs[1]);
    
    // 绑定第二个顶点缓冲
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
    // 设置第二个顶点数组的顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
    
    // 启用第二个顶点属性数组
    glEnableVertexAttribArray(0);
    
    // 解绑第二个缓存数组
//    glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)

    
    
    // 画线框
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    
    // 循环渲染
    while (!glfwWindowShouldClose(window))
    {
        // 处理鼠标、键盘输入
        processInput(window);
        
        // 设置窗体颜色
        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // 激活着色器程序
        glUseProgram(shaderProgramId);
        
        // 画第一个三角形
        glBindVertexArray(vertexArrayObjs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        // 画第二个三角形
        glBindVertexArray(vertexArrayObjs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        // 交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // 释放资源
    glDeleteBuffers(2, vertexBufferObjs);
    glDeleteVertexArrays(2, vertexArrayObjs);
    glfwTerminate();
    
    return 0;
}


void framBufferSizeCallback(GLFWwindow *window, GLint width, GLint height)
{
    std::cout << "window-width = " << width << " window-height = " << height << std::endl;
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow *window)
{
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
