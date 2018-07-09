//
//  objectVS.glsl
//  MultipleLights
//
//  Created by shenyuanluo on 2017/8/22.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘物体’顶点着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec3 aPos;         /* 顶点位置变量的属性位置值为：0 */
layout (location = 1) in vec3 aNormal;      /* 顶点‘法向量’的属性位置为：1 */
layout (location = 2) in vec2 aTexCoords;   /* 顶点‘纹理坐标’的属性位置为：1 */

out vec3 FragPos;       /* 输出，片段位置向量 */
out vec3 Normal;        /* 输出，法向量传递给片段着色器 */
out vec2 TexCoords;     /* 输出，顶点纹理坐标 */

uniform mat4 modelMat;                  /* 模型矩阵 */
uniform mat4 viewMat;                   /* 观察矩阵 */
uniform mat4 projectionMat;             /* 投影矩阵 */

uniform mat3 NormalMat;                 /* 法线矩阵(用于物体变换后法线跟着变换):模型矩阵左上角的逆矩阵的转置矩阵，
                                           并且是 3x3 */

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
    FragPos = vec3(modelMat * vec4(aPos, 1.0)); /* 通过模型矩阵转换至世界空间坐标 */
    Normal  = NormalMat * aNormal;
    TexCoords = aTexCoords;
}
