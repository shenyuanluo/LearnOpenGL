//
//  PointsGS.glsl
//  GeometryShader
//
//  Created by shenyuanluo on 2017/9/8.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘点’几何着色器
 */


#version 330 core       /* 指定 GLSL 版本3.3，匹配 OpenGL 版本 */

layout (points) in;     /* 指定几何着色器输入的图元类型 */

layout (line_strip, max_vertices = 2) out;  /* 指定几何着色器输出的图元类型和最大能够输出的顶点数量 */

/* GLSL 内建变量：'gl_in' 大致结构如下
in gl_Vertex
{
    vec4  gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
} gl_in[];
*/

void main()
{
    /* 修改顶点位置向量 */
    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);
    /* 几何着色器函数，将 gl_Position 中的(位置)向量添加到图元中，
     即：发射出新顶点 */
    EmitVertex();
    
    /* 修改顶点位置向量 */
    gl_Position = gl_in[0].gl_Position + vec4( 0.1, 0.0, 0.0, 0.0);
    /* 发射新顶点 */
    EmitVertex();
    
    /* 几何着色器函数，将发射出的(Emitted)顶点合成为指定的输出渲染图元 */
    EndPrimitive();
}
