//
//  main.cpp
//  TexturesExercise1
//
//  Created by shenyuanluo on 2017/10/3.
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
    
    // 定义 矩形顶点数据数组
    GLfloat vertices[] =
    {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // top left
    };
    
    renView.render(vertices, sizeof(vertices));
    
    return 0;
}
