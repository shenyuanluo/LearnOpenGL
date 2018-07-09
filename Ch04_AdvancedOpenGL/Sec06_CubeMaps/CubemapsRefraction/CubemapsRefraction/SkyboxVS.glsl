//
//  SkyboxVS.glsl
//  CubemapsRefraction
//
//  Created by shenyuanluo on 2017/9/6.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘天空盒’顶点着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */
layout (location = 0) in vec3 aPos; /* 顶点位置变量的属性位置值为：0 */

out vec3 TexCoords;

/* 不需要模型矩阵，因为天空盒中心就位于世界空间原点位置 */
uniform mat4 viewMat;                   /* 观察矩阵 */
uniform mat4 projectionMat;             /* 投影矩阵 */


void main()
{
    TexCoords = aPos;
    vec4 pos = projectionMat * viewMat * vec4(aPos, 1.0);
    /* 'pos.xyww'：最终的标准化设备坐标将永远会有一个等于1.0的z值：最大的深度值。
     结果就是天空盒只会在没有可见物体的地方渲染了
     （只有这样才能通过深度测试，其它所有的东西都在天空盒前面）。
     同时，要改深度函数，将它从默认的 ‘GL_LESS’ 改为 ‘GL_LEQUAL’。
     深度缓冲将会填充上天空盒的 1.0 值，所以需要保证天空盒在值小于或等于深度缓冲而不是小于时通过深度测试。 */
    gl_Position = pos.xyww;
}
