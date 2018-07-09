//
//  ExplodeGS.glsl
//  GeometryShaderExplode
//
//  Created by shenyuanluo on 2017/9/8.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘爆破’几何着色器
 */


#version 330 core       /* 指定 GLSL 版本3.3，匹配 OpenGL 版本 */

layout (triangles) in;      /* 指定几何着色器输入的图元类型 */

layout (triangle_strip, max_vertices = 3) out;  /* 指定几何着色器输出的图元类型和最大能够输出的顶点数量 */

/* 输入接口块
 因为几何着色器是作用于输入的一组顶点的，
 从顶点着色器发来输入数据总是会以数组的形式表示出来。 */
in VS_OUT {
    vec2 texCoords;     // 输入，纹理坐标
} gs_in[];

out vec2 TexCoords;     // 输出，纹理坐标

uniform float timeValue;     // 时间

/**
 计算(三角形图元)单位法向量
 
 return 单位法向量
 */
vec3 GetNormal()
{
    // 计算平行于三角形图元平面的向量：a
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    // 计算平行于三角形图元平面的向量：b
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    // 通过叉乘计算三角形图元的法向量
    return normalize(cross(a, b));
}

/**
 计算(三角形图元)爆破后的位置向量
 
 @param position 顶点位置向量
 @param normal 顶点法向量
 @return 顶点爆破后的位置向量
 */
vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 0.5;  // 爆破级别
    // 爆破距离
    vec3 direction = normal * ((sin(timeValue) + 1.0) / 2.0) * magnitude;
    // 沿着法向量位移(爆破)距离
    return position + vec4(direction, 0.0);
}

void main()
{
    vec3 normal = GetNormal();
    
    gl_Position = explode(gl_in[0].gl_Position, normal);    // 计算三角形图元顶点 1 爆破位置
    TexCoords = gs_in[0].texCoords;
    EmitVertex();   /* 发射顶点 */
    gl_Position = explode(gl_in[1].gl_Position, normal);    // 计算三角形图元顶点 2 爆破位置
    TexCoords = gs_in[1].texCoords;
    EmitVertex();   /* 发射顶点 */
    gl_Position = explode(gl_in[2].gl_Position, normal);    // 计算三角形图元顶点 3 爆破位置
    TexCoords = gs_in[2].texCoords;
    EmitVertex();   /* 发射顶点 */
    EndPrimitive(); /* 将发射出的(Emitted)顶点合成为指定的输出渲染图元 */
}
