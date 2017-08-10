//
//  HelloWindow.cpp
//  HelloWindow
//
//  Created by shenyuanluo on 2017/8/10.
//  Copyright © 2017年 http://blog.shenyuanluo.com/. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


// 声明 GLFW window 大小改变回调
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// 声明 处理用户输入
void processInput(GLFWwindow *window);

int main()
{
    // 初始化 GLFW
    glfwInit();
    // 告诉 GLFW 使用的 OpenGL 版本为：3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 使用 OpenGL 的 Core-profile 模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__ // macOS 系统标志
    // 指定 OpenGL 上下文需要向前兼容
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    
    // 创建 GLFWWindow 对象
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello window", NULL, NULL);
    if (NULL == window)
    {
        std::cout << "创建 GLFW 窗体失败！" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 通知 GLFW 将窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);
    // 注册 GLFW window 大小改变的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    
    // GLAD 是用来管理 OpenGL 的函数指针的，所以在调用任何 OpenGL 的函数之前先需要初始化GLAD。(GLFW 给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD 初始化失败！" << std::endl;
        return -1;
    }
    
    // 添加渲染循环
    while (!glfwWindowShouldClose(window))
    {
        // 输入
        processInput(window);
        
        // 渲染
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 状态设置函数
        glClear(GL_COLOR_BUFFER_BIT);           // 状态使用函数
        
        
        // 交换缓存
        glfwSwapBuffers(window);
        // 检查是否有事件（键盘输入或鼠标移动）更新窗体状态
        glfwPollEvents();
    }
    
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

