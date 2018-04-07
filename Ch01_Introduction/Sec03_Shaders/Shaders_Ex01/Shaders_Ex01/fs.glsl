//
//  fs.glsl
//  Shaders_Ex01
//
//  Created by shenyuanluo on 2017/8/12.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 片段着色器
 */


#version 330 core   /* 指定GLSL版本3.3，匹配 OpenGL 版本 */


in vec3 vertexColor;    /* 输入，接收顶点颜色，从顶点着色器传来的输入变量（名称相同、类型相同） */

out vec4 FragColor;     /* 输出，指定片段颜色 */

void main()
{
    FragColor = vec4(vertexColor, 1.0f);
}
