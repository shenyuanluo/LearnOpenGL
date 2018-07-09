//
//  main.cpp
//  Shaders
//
//  Created by shenyuanluo on 2017/8/12.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "Window.hpp"


int main(int argc, const char * argv[])
{
    Window window(800, 600, "Shaders");
    
    window.setCWD(argv[0]);
    
    GLfloat vertices[] =
    {
        // 顶点位置             // 顶点颜色
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  /* 右下角 顶点 */
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  /* 左下角 顶点 */
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   /* 顶部 顶点 */
    };
    
    window.render(vertices, sizeof(vertices));
    
    return 0;
}
