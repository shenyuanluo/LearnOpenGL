//
//  AdvanceGLSLVS.glsl
//  AdvancedGLSL
//
//  Created by shenyuanluo on 2017/9/7.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘高级 GLSL’顶点着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

layout (location = 0) in vec3 aPos;         /* 顶点位置变量的属性位置值为：0 */

uniform mat4 modelMat;          /* 模型矩阵 */

/* 该 Uniform 块使用 std140 布局 */
layout (std140) uniform Matrices
{
    /* 观察矩阵 */          // 基准对齐量      // 对齐偏移量
    mat4 viewMat;         //    16          //  0   (列 0)
                          //    16          //  16  (列 1)
                          //    16          //  32  (列 2)
                          //    16          //  48  (列 3)
    /* 投影矩阵 */
    mat4 projectionMat;
                          //    16          //  64   (列 0)
                          //    16          //  80   (列 1)
                          //    16          //  96   (列 2)
                          //    16          //  112  (列 3)
};

void main()
{
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
}
