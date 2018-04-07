//
//  vs.glsl
//  Shaders
//
//  Created by shenyuanluo on 2017/8/12.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 顶点着色器
 */



#version 330 core   /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec3 aPos;     /* 顶点位置变量的属性位置值为：0 */
layout (location = 1) in vec3 aColor;   /* 顶点颜色变量的属性位置值为：1 */

out vec3 vertexColor;                   /* 输出，指定顶点颜色（传递给片段着色器） */

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = aColor;   /* 从顶点数据读入的颜色数据传递给‘片段着色器’ */
}
