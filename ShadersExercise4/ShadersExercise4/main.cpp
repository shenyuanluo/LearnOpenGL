//
//  main.cpp
//  ShadersExercise4
//
//  Created by shenyuanluo on 2017/10/1.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "RenderView.h"



int main()
{
    const GLuint scrWidth  = 800;
    const GLuint scrHeight = 600;
    const GLchar* scrTitle = "Shaders";
    
    RenderView renView(scrWidth, scrHeight, scrTitle);
    
    if (RetError == renView.initGlad())
    {
        return -1;
    }
    
    // 定义 三角形顶点数据数组
    GLfloat vertices[] =
    {
        // 顶点位置               // 颜色
         0.0f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,           // 上顶点
        -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,           // 左下角 顶点
         0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,           // 右下角 顶点
    };
    
    renView.render(vertices, sizeof(vertices));
    
    return 0;
}
