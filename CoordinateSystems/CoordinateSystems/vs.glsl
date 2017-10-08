//
//  vs.glsl
//  Shaders
//
//  Created by shenyuanluo on 2017/9/6.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#version 330 core       // 指定GLSL版本3.3
layout (location = 0) in vec3 aPos;         // 顶点位置变量的属性为 0
layout (location = 1) in vec3 aColor;       // 顶点颜色变量的属性为 1
layout (location = 2) in vec2 aTexCoord;    // 顶点纹理变量的属性为 2

out vec3 vertexColor;   // 输出颜色到 ‘片段着色器’
out vec2 texCoord;      // 输出纹理坐标到‘片段着色器’

uniform mat4 modelMat;          // '模型'矩阵
uniform mat4 viewMat;           // ‘观察’矩阵
uniform mat4 projectionMat;     // ‘投影’矩阵

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
    vertexColor = aColor;       // 从顶点数据读入的颜色数据传递给‘片段着色器’
    texCoord    = aTexCoord;    // 从顶点数据读入的纹理坐标数据传递给‘片段着色器’
}
