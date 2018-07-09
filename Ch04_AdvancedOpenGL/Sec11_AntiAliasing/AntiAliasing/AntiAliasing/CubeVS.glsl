//
//  CubeVS.glsl
//  AntiAliasing
//
//  Created by shenyuanluo on 2017/9/10.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘箱子’顶点着色器
 */


#version 330 core       /* 指定 GLSL 版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec3 aPos;     /* 顶点位置变量的属性位置值为：0 */

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main()
{
    gl_Position  = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
}
