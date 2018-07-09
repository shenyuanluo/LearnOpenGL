//
//  CubeFS.glsl
//  AntiAliasing
//
//  Created by shenyuanluo on 2017/9/10.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘箱子’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

out vec4 FragColor;     /* 输出，指定片段颜色 */

void main()
{
    FragColor = vec4(0.5, 1.0, 0.5, 1.0);
}
