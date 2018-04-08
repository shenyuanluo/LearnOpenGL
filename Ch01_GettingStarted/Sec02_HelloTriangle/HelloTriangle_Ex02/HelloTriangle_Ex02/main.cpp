//
//  main.cpp
//  HelloTriangle_Ex02
//
//  Created by shenyuanluo on 2017/8/11.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "Window.hpp"


int main(int argc, const char * argv[])
{
    Window window(800, 600, "Hello Triangle Ex02");
    
    // 第一个三角形
    GLfloat vertices1[] =
    {
        -0.8f, -0.3f, 0.0f,         // 左下角顶点
        -0.2f, -0.3f, 0.0f,         // 右下角顶点
        -0.5f,  0.3f, 0.0f,         // 上顶点
    };
    
    // 第二个三角形
    GLfloat vertices2[] =
    {
        0.2f, -0.3f, 0.8f,          // 左下顶点
        0.8f, -0.3f, 0.0f,          // 右下顶点
        0.5f,  0.3f, 0.0f,          // 上顶点
    };
    
    window.render(vertices1, sizeof(vertices1), vertices2, sizeof(vertices2));
    
    return 0;
}
