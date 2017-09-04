//
//  main.cpp
//  HelloTriangleExercise2
//
//  Created by shenyuanluo on 2017/8/25.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "HelloTriangleExercise2.h"


int main ()
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
    
    render(window, triangle1, sizeof(triangle1), triangle2, sizeof(triangle2));
    glfwTerminate();
    
    return 0;
}
