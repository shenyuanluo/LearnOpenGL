//
//  FBInversionFS.glsl
//  FramebuffersInversion
//
//  Created by shenyuanluo on 2017/9/5.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘帧缓冲（反相）’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

in vec2 TexCoords;      /* 输入，接收顶点颜色，从顶点着色器传来的输入变量（名称相同、类型相同） */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform sampler2D screenTexture;    /* 纹理采样 */

void main()
{
    /* （帧缓冲）后期处理·反相
       取颜色值，然后用 1.0 减去它，即可进行反相*/
    FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
}
