//
//  main.cpp
//  HelloTriangleExercise1
//
//  Created by shenyuanluo on 2017/8/21.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "HelloTriangleExercise1.h"



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
    
    render(window, vertices, sizeof(vertices));

    // 退出 GLFW
    glfwTerminate();
    
    
    return 0;
}

