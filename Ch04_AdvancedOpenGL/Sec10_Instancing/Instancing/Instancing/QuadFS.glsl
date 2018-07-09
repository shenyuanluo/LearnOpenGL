//
//  QuadFS.glsl
//  Instancing
//
//  Created by shenyuanluo on 2017/9/9.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘四边形’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

in vec3 fColor;         /* 输入，颜色值 */

out vec4 FragColor;     /* 输出，指定片段颜色 */

void main()
{
    FragColor = vec4(fColor, 1.0);
}

