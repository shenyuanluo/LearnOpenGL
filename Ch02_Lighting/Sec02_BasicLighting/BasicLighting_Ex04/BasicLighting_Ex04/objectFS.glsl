//
//  objectFS.glsl
//  BasicLighting_Ex04
//
//  Created by shenyuanluo on 2017/8/18.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘物体’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

in vec3 LightColor;     /* 输入，光照拟合颜色 */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform vec3 objectColor;   /* 设定物体颜色 */

void main()
{    
    FragColor = vec4(LightColor * objectColor, 1.0);
}
