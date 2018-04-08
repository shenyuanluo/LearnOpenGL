//
//  main.cpp
//  HelloTriangle_Ex01
//
//  Created by shenyuanluo on 2017/8/11.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "Window.hpp"


int main(int argc, const char * argv[])
{
    Window window(800, 600, "Hello Triangle Ex01");
    
    GLfloat vertices[] =
    {
        // 第一个三角形
        -0.5f,  -0.5f,  0.0f,           // 左下顶点
         0.0f,  -0.5f,  0.0f,           // 右下顶点
        -0.25f,  0.25f, 0.0f,           // 上顶点
        // 第二个三角形
         0.0f,  -0.5f,  0.0f,           // 左下顶点
         0.5f,  -0.5f,  0.0f,           // 右下顶点
         0.25f,  0.25f, 0.0f,           // 上顶点
    };
    
    window.render(vertices, sizeof(vertices));
    
    return 0;
}
