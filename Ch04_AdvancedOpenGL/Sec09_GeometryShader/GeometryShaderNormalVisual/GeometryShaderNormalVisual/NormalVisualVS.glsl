//
//  NormalVisualVS.glsl
//  GeometryShaderNormalVisual
//
//  Created by shenyuanluo on 2017/9/8.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘法向量可视化’顶点着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec3 aPos;         /* 顶点位置变量的属性位置值为：0 */
layout (location = 1) in vec3 aNormal;      /* 顶点‘法向量’的属性位置为：1 */

/* 输出接口块 */
out VS_OUT {
    vec3 normal;     // 输出，法向量
} vs_out;

uniform mat4 modelMat;                  /* 模型矩阵 */
uniform mat4 viewMat;                   /* 观察矩阵 */
uniform mat4 projectionMat;             /* 投影矩阵 */


void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
    /* 法线矩阵：模型矩阵(或观察矩阵)左上角的逆矩阵的转置矩阵 */
    mat3 normalMatrix = mat3(transpose(inverse(viewMat * modelMat)));
    /* 为了适配（观察和模型矩阵的）缩放和旋转，
     在将法线变换到裁剪空间坐标之前，先使用法线矩阵变换一次：normalMatrix * aNormal；
     再将法向量转换到裁剪空间中(因为几何着色器接受的位置向量是剪裁空间坐标) */
    vs_out.normal = normalize(vec3(projectionMat * vec4(normalMatrix * aNormal, 0.0)));
}
