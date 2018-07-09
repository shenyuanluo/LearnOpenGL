//
//  modeLoadingFS.glsl
//  InstancingAsteroidBelt
//
//  Created by shenyuanluo on 2017/9/9.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘Nanosuit’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

/* 输入接口块 */
in VS_OUT {
    vec2 texCoords;     // 输入，纹理坐标
} fs_in;

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = texture(texture_diffuse1, fs_in.texCoords);
}
