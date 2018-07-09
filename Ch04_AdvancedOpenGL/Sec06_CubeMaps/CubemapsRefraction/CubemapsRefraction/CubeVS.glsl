//
//  CubeFS.glsl
//  CubemapsRefraction
//
//  Created by shenyuanluo on 2017/9/6.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘箱子’顶点着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec3 aPos;         /* 顶点位置变量的属性位置值为：0 */
layout (location = 1) in vec3 aNormal;      /* 顶点法向量的属性位置值为：1 */

out vec3 Normal;            /* 顶点法向量 */
out vec3 Position;          /* 顶点位置向量 */

uniform mat4 modelMat;          /* 模型矩阵 */
uniform mat4 viewMat;           /* 观察矩阵 */
uniform mat4 projectionMat;     /* 投影矩阵 */

void main()
{
    /* 法线矩阵：模型矩阵左上角的逆矩阵的转置矩阵 */
    mat4 normalMat = transpose(inverse(modelMat));
    /* 使用法线矩阵计算法线向量 */
    Normal = mat3(normalMat) * aNormal;
    /* (世界空间)顶点位置向量 */
    Position = vec3(modelMat * vec4(aPos, 1.0));
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
}
