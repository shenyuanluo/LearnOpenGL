//
//  main.cpp
//  HelloTriangleExercise3
//
//  Created by shenyuanluo on 2017/9/3.
//  Copyright © 2017年 shenyuanluo. All rights reserved.
//

#include <iostream>
#include "HelloTriangleExercise3.h"


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
    
    // -------------------------- 画三角形 --------------------------
    // 定义 第一个三角形顶点数据数组
    GLfloat firstTriangle[] =
    {
        -0.9f, -0.5f, 0.0f,             // 左下角 顶点
        -0.0f, -0.5f, 0.0f,             // 右下角 顶点
        -0.45f, 0.5f, 0.0f,             // 上 顶点
    };
    
    // 定义 第二个三角形顶点数据数组
    GLfloat secondTriangle[] = {
        0.0f, -0.5f, 0.0f,              // 左下角 顶点
        0.9f, -0.5f, 0.0f,              // 右下角 顶点
        0.45f, 0.5f, 0.0f               // 上 顶点
    };
    
    render(window, firstTriangle, sizeof(firstTriangle), secondTriangle, sizeof(secondTriangle));
    
    // 退出 GLFW
    glfwTerminate();
    
    return 0;
}
