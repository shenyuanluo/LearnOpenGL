//
//  FaceCullingFS.glsl
//  FaceCulling_Ex01
//
//  Created by shenyuanluo on 2017/9/4.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘面剔除’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

in vec2 TexCoords;      /* 输入，接收顶点颜色，从顶点着色器传来的输入变量（名称相同、类型相同） */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform sampler2D texture1; /* 纹理采样 1 */


void main()
{
    vec4 texColor = texture(texture1, TexCoords);
    /* 丢弃透明的片段，不将这些片段存储到颜色缓冲中 */
    if(texColor.a < 0.1)
    {
        discard;
    }
    FragColor = texColor;
}
