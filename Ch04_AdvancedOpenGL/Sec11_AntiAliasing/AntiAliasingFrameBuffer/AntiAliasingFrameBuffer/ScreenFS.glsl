//
//  ScreenFS.glsl
//  AntiAliasing
//
//  Created by shenyuanluo on 2017/9/10.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘屏幕·帧’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

in vec2 TexCoords;      /* 输入，接收顶点颜色，从顶点着色器传来的输入变量（名称相同、类型相同） */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform sampler2D screenTexture;    /* 纹理采样 */

void main()
{
    vec3 col = texture(screenTexture, TexCoords).rgb;
    FragColor = vec4(col, 1.0);
}
