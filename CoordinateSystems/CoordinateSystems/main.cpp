//
//  main.cpp
//  CoordinateSystems
//
//  Created by shenyuanluo on 2017/10/8.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "RenderView.h"


int main()
{
    const GLuint scrWidth  = 800;
    const GLuint scrHeight = 600;
    const GLchar* scrTitle = "CoordinateSystems";
    
    RenderView renView(scrWidth, scrHeight, scrTitle);
    
    if (RetError == renView.initGlad())
    {
        return -1;
    }
    
    // 定义 矩形顶点数据数组
    GLfloat vertices[] =
    {
        // 位置坐标             // 颜色             // 纹理坐标
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,       // 右上顶点
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,       // 右下顶点
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,       // 左下顶点
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,       // 左上顶点
    };
    
    renView.render(vertices, sizeof(vertices));
    
    return 0;
}
