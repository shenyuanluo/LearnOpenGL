//
//  main.cpp
//  HelloTriangle_Ex03
//
//  Created by shenyuanluo on 2017/8/11.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "Window.hpp"


int main(int argc, const char * argv[])
{
    Window window(800, 600, "Hello Triangle Ex03");
    
    // 第一个三角形
    GLfloat vertices1[] =
    {
        -0.9f, -0.5f, 0.0f,             // 左下角 顶点
        -0.0f, -0.5f, 0.0f,             // 右下角 顶点
        -0.45f, 0.5f, 0.0f,             // 上 顶点
    };
    
    // 第二个三角形
    GLfloat vertices2[] = {
        0.0f, -0.5f, 0.0f,              // 左下角 顶点
        0.9f, -0.5f, 0.0f,              // 右下角 顶点
        0.45f, 0.5f, 0.0f               // 上 顶点
    };
    
    window.render(vertices1, sizeof(vertices1), vertices2, sizeof(vertices2));
    
    return 0;
}
