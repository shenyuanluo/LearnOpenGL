//
//  objectVS.glsl
//  BasicLighting_Ex04
//
//  Created by shenyuanluo on 2017/8/18.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘物体’顶点着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec3 aPos;     /* 顶点位置变量的属性位置值为：0 */
layout (location = 1) in vec3 aNormal;  /* 顶点‘法向量’的属性位置为：0 */

out vec3 LightColor;        /* 输出，光照拟合颜色 */

uniform mat4 modelMat;                  /* 模型矩阵 */
uniform mat4 viewMat;                   /* 观察矩阵 */
uniform mat4 projectionMat;             /* 投影矩阵 */

uniform mat3 NormalMat;                 /* 法线矩阵(用于物体变换后法线跟着变换):模型矩阵左上角的逆矩阵的转置矩阵，
                                           并且是 3x3 */
uniform vec3 lightColor;    /* 设定灯光颜色 */
uniform vec3 lightPos;      /* 光源位置向量 */
uniform vec3 viewerPos;     /* 观察者位置向量 */

uniform float ambientStrenth;   /* 环境因子（强度） */
uniform float specularStrength; /* 镜面因子（强度） */
uniform int shininess;          /* 反光因子（强度）*/

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
    
    /* ========== Gouraud 着色 ==========  */
    /* 通过模型矩阵，计算片段的世界空间坐标 */
    vec3 fragPos = vec3(modelMat * vec4(aPos, 1.0));
    /* 计算经过‘法线矩阵’处理的法向量 */
    vec3 normal  = NormalMat * aNormal;
    
    /* ========== '环境光照'处理 ========== */
    /* 环境光照 */
    vec3 ambientLight = ambientStrenth * lightColor;
    
    
    /* ========== '漫反射光照'处理 ========== */
    vec3 norm = normalize(normal);  /* 将法向量标准化（单位向量）*/
    /* 光源方向向量 = 光源位置向量 - 片段位置向量
     (将光源方向向量标准化（单位向量）)*/
    vec3 lightDir = normalize(lightPos - fragPos);  /*  */
    /*
     漫反射（对光照的）影响 = 单位法向量 · 单位光照方向向量
     max 保证结果为正数，从而保证漫反射分量不会变成负数。
     负数颜色的光照是没有定义的*/
    float diffuseEffect = max(dot(norm, lightDir), 0.0f);
    /* 漫反射光照 */
    vec3 diffuseLight = diffuseEffect * lightColor;
    
    
    /* ========== '镜面光照'处理 ========== */
    /* 观察者方向向量 = 观察者位置向量 - 片段位置向量 */
    vec3 viewerDir = normalize(viewerPos - fragPos);
    /*
     沿着法线轴的'反射'向量
     注意: reflect 函数要求第一个向量是从光源指向片段位置的向量，
     但是 lightDir 当前正好相反，所以对 lightDir 向量进行了取反；
     第二个参数要求是一个法向量。
     */
    vec3 reflectDir = reflect(-lightDir, norm);
    /* 镜面影响
     pow 是‘取幂’函数，shininess：是‘次幂’
     表示的是：高光的‘反光度’ （一个物体的反光度越高，反射光的能力越强，散射得越少，高光点就会越小，
     反光度：2、4、8、16、32、64、128、256 ） */
    float specularEffect = pow(max(dot(viewerDir, reflectDir), 0.0), shininess);
    /* 镜面光照 = 镜面强度 * 镜面影响 * 光照颜色 */
    vec3 specularLight = specularStrength * specularEffect * lightColor;
    
    
    /* 最终光照拟合颜色
       环境光分量 + 漫反射分量 + 镜面分量
     */
    LightColor = ambientLight + diffuseLight + specularLight;
}
