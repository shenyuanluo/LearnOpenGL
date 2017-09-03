//
//  main.cpp
//  HelloTriangle
//
//  Created by shenyuanluo on 2017/8/13.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "HelloTriangle.h"
#include <iostream>


int main()
{
    GLFWwindow *window = initWindow();
    if (!window)
    {
        return -1;
    }
    
    if (RetError == initGlad())
    {
        return -1;
    }
    
    // -------------------------- 画矩形 --------------------------
    // 定义 矩形顶点数据数组
    GLfloat vertices[] =
    {
        -0.5f,  0.5f, 0.0f,             // 左上角 顶点
         0.5f,  0.5f, 0.0f,             // 右上角 顶点
        -0.5f, -0.5f, 0.0f,             // 左下角 顶点
         0.5f, -0.5f, 0.0f,             // 右下角 顶点
    };
    
    render(window, vertices, sizeof(vertices));

    
    // 退出 GLFW
    glfwTerminate();
    
    return 0;
}




