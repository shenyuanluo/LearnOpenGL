//
//  main.cpp
//  Textures_Ex03
//
//  Created by shenyuanluo on 2017/8/13.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include <iostream>
#include "Window.hpp"


int main(int argc, const char * argv[])
{
    Window window(800, 600, "Textures Ex03");
    
    GLfloat vertices[] =
    {
        // 顶点坐标             // 颜色             // 文理坐标
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f,   /* 右上角 顶点 */
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f,   /* 右下角 顶点 */
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f,   /* 左下角 顶点 */
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f,   /* 左上角 顶点 */
    };
    window.render(vertices, sizeof(vertices));
    
    return 0;
}
