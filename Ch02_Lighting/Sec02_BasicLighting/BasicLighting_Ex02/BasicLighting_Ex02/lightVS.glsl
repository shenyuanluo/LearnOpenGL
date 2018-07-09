//
//  lightVS.glsl
//  BasicLighting_Ex02
//
//  Created by shenyuanluo on 2017/8/18.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘光源’顶点着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec3 aPos;     /* 顶点位置变量的属性位置值为：0 */

uniform mat4 modelMat;                  /* 模型矩阵 */
uniform mat4 viewMat;                   /* 观察矩阵 */
uniform mat4 projectionMat;             /* 投影矩阵 */

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
}
