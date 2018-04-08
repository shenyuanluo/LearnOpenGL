//
//  main.cpp
//  HelloTriangle
//
//  Created by shenyuanluo on 2017/8/11.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "Window.hpp"


int main(int argc, const char * argv[])
{
    Window window(800, 600, "Hello Triangle");
    
    GLfloat vertices[] =
    {
        -0.5f,  0.5f,  0.0f,            // 左上角 顶点
         0.5f,  0.5f,  0.0f,            // 右上角 顶点
        -0.5f, -0.5f,  0.0f,            // 左下角 顶点
         0.5f, -0.5f,  0.0f,            // 右下角 顶点
    };
    
    window.render(vertices, sizeof(vertices));
    
    return 0;
}
