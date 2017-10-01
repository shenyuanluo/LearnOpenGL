//
//  vs.glsl
//  Shaders
//
//  Created by shenyuanluo on 2017/9/6.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#version 330 core       // 指定GLSL版本3.3
layout (location = 0) in vec3 aPos;     // 顶点位置变量的属性为 0
layout (location = 1) in vec3 aColor;   // 顶点颜色变量的属性为 1

out vec3 customColor;   // 输出颜色到 ‘片段着色器’

void main()
{
    gl_Position = vec4(aPos, 1.0);
    customColor = aColor;   // 从顶点数据读入的颜色数据传递给‘片段着色器’
}
