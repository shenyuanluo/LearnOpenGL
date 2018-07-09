//
//  TriangleGS.glsl
//  GeometryShader
//
//  Created by shenyuanluo on 2017/9/8.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘三角形’几何着色器
 */


#version 330 core       /* 指定 GLSL 版本3.3，匹配 OpenGL 版本 */

layout (points) in;     /* 指定几何着色器输入的图元类型 */

layout (triangle_strip, max_vertices = 5) out;  /* 指定几何着色器输出的图元类型和最大能够输出的顶点数量 */

/* 输入接口块
  因为几何着色器是作用于输入的一组顶点的，
  从顶点着色器发来输入数据总是会以数组的形式表示出来。 */
in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fColor;    /* 输出颜色传递给片段着色器 */

/* GLSL 内建变量：'gl_in'
in gl_Vertex
{
    vec4  gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
} gl_in[];
*/

/*
 利用几何着色器发射新顶点合成三角形图元来画房子
 
                                        /\
                                       /  \
                                      /    \
                                     /      \
                                    /        \
                                    ----------
                                    |\       |
                                    | \      |
                                    |  \     |
                                    |   \    |
                                    |    ·   |
                                    |     \  |
                                    |      \ |
                                    |       \|
                                    ----------
 */

void buildHouse(vec4 position)
{
    /* 当发射一个顶点的时候，每个顶点将会使用'最后'在 fColor 中储存的值，
       来用于片段着色器的运行
     */
    fColor = gs_in[0].color;    // gs_in[0] 因为(points类型的图元)只有一个输入顶点
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:左下
    EmitVertex();   /* 发射出新顶点 */
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:右下
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:左上
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:右上
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:顶部
    fColor = vec3(1.0, 1.0, 1.0);   // 将屋顶的顶点的颜色设置为白色(模拟下雪)
    EmitVertex();
    EndPrimitive();     /* 将发射出的(Emitted)顶点合成为指定的输出渲染图元 */
}

void main()
{
    buildHouse(gl_in[0].gl_Position);
}
