//
//  AdvanceGLSLFS.glsl
//  AdvancedGLSL
//
//  Created by shenyuanluo on 2017/9/7.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘高级 GLSL’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

out vec4 FragColor;     /* 输出，指定片段颜色 */

void main()
{
    FragColor = vec4(0.0, 0.0, 1.0, 1.0);
}

