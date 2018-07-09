//
//  QuadVS.glsl
//  Instancing
//
//  Created by shenyuanluo on 2017/9/9.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘四边形’顶点着色器
 */


#version 330 core       /* 指定 GLSL 版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec2 aPos;     /* 顶点位置变量的属性位置值为：0 */
layout (location = 1) in vec3 aColor;   /* 顶点颜色变量的属性位置值为：1 */

out vec3 fColor;    // 输出，颜色

uniform vec2 offsets[100];  // 偏移

void main()
{
    /* 顶点着色器内建变量：‘gl_InstanceID’
     在使用实例化渲染调用(glDrawArraysInstanced 和 glDrawElementsInstanced)时，
     gl_InstanceID 会从 0 开始，在每个实例被渲染时递增 1 */
    vec2 offset = offsets[gl_InstanceID];
    gl_Position = vec4(aPos + offset, 0.0, 1.0);
    fColor = aColor;
}
