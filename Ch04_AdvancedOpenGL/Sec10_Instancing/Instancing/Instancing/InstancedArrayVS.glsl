//
//  QuadVS.glsl
//  Instancing
//
//  Created by shenyuanluo on 2017/9/9.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘四边形·实例化数组’顶点着色器
 */


#version 330 core       /* 指定 GLSL 版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec2 aPos;     /* 顶点位置变量的属性位置值为：0 */
layout (location = 1) in vec3 aColor;   /* 顶点颜色变量的属性位置值为：1 */
layout (location = 2) in vec2 aOffset;  /* 顶点偏移量的属性位置值为：2 */

out vec3 fColor;    // 输出，颜色

void main()
{
//    vec2 pos = aPos;    // 常规显示
    
    vec2 pos = aPos * (gl_InstanceID / 100.0);  // 从右上到左下逐渐缩小四边形
    
    gl_Position = vec4(pos + aOffset, 0.0, 1.0);
    
    fColor = aColor;
}
