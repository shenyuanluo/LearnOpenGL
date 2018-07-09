//
//  objectFS.glsl
//  Camera
//
//  Created by shenyuanluo on 2017/8/17.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘物体’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform vec3 objectColor;   /* 设定物体颜色 */
uniform vec3 lightColor;    /* 设定灯光颜色 */

void main()
{
    FragColor = vec4(lightColor * objectColor, 1.0);
}
