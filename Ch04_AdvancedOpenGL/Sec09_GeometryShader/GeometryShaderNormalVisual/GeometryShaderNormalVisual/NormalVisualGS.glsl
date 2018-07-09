//
//  NormalVisualVS.glsl
//  GeometryShaderNormalVisual
//
//  Created by shenyuanluo on 2017/9/8.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘法向量可视化’几何着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

layout (triangles) in;  /* 指定几何着色器输入的图元类型 */

layout (line_strip, max_vertices = 6) out;  /* 指定几何着色器输出的图元类型和最大能够输出的顶点数量 */

/* 输入接口块
 因为几何着色器是作用于输入的一组顶点的，
 从顶点着色器发来输入数据总是会以数组的形式表示出来。 */
in VS_OUT {
    vec3 normal;
} gs_in[];

const float magnitude  = 0.1;    // 等级

/**
 生成法线
 
 @param index 顶点下标
 */
void GenerateNormal(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();   /* 发射顶点 */
    /* 将顶点位置沿着法向量平移一段距离 */
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * magnitude ;
    EmitVertex();   /* 发射顶点 */
    EndPrimitive(); /* 将发射出的(Emitted)顶点合成为指定的输出渲染图元：line_strip */
}

void main()
{
    /* 三角形图元有三个顶点 */
    for (int index = 0; index < 3; index++)
    {
       GenerateNormal(index);
    }
}
