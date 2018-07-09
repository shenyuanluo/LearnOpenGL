//
//  vs.glsl
//  HelloTriangle_Ex01
//
//  Created by shenyuanluo on 2017/8/11.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 顶点着色器
 */


#version 330 core   /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec3 aPos; /* 顶点位置变量的属性位置值为：0 */

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
