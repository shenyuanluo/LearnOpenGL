//
//  modeLoadingFS.glsl
//  GeometryShaderNormalVisual
//
//  Created by shenyuanluo on 2017/9/8.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘Nanosuit’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

/* 输入接口块
 因为几何着色器是作用于输入的一组顶点的，
 从顶点着色器发来输入数据总是会以数组的形式表示出来。 */
in VS_OUT {
    vec2 texCoords;     // 输入，纹理坐标
} fs_in;
//in vec2 TexCoords;      /* 输入，纹理坐标 */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = texture(texture_diffuse1, fs_in.texCoords);
}
