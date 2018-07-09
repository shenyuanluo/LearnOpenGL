//
//  FBKernelFS.glsl
//  FramebuffersKernel
//
//  Created by shenyuanluo on 2017/9/5.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘帧缓冲（核）’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

in vec2 TexCoords;      /* 输入，接收顶点颜色，从顶点着色器传来的输入变量（名称相同、类型相同） */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform sampler2D screenTexture;    /* 纹理采样 */

uniform int kernelType;

const float offset = 1.0 / 300.0;

/**
 锐化处理
 
 @param inTexture 纹理采样
 @param inTexCoords 纹理坐标
 @return 锐化结果纹理颜色
 */
vec3 sharpen(sampler2D inTexture, vec2 inTexCoords);

/**
 模糊处理
 
 @param inTexture 纹理采样
 @param inTexCoords 纹理坐标
 @return 锐化结果纹理颜色
 */
vec3 blur(sampler2D inTexture, vec2 inTexCoords);

/**
 边缘检测
 
 @param inTexture 纹理采样
 @param inTexCoords 纹理坐标
 @return 锐化结果纹理颜色
 */
vec3 edgeDetection(sampler2D inTexture, vec2 inTexCoords);

void main()
{
    vec3 result;
    
    if (0 == kernelType)        // 锐化
    {
        result = sharpen(screenTexture, TexCoords);
    }
    else if (1 == kernelType)   // 模糊
    {
        result = blur(screenTexture, TexCoords);
    }
    else if (2 == kernelType)   // 边缘检测
    {
        result = edgeDetection(screenTexture, TexCoords);
    }
    else    // 原图
    {
        result = vec3(texture(screenTexture, TexCoords));
    }
   
    FragColor = vec4(result, 1.0);
}

/* 锐化处理 */
vec3 sharpen(sampler2D inTexture, vec2 inTexCoords)
{
    // 针对 3x3 核的偏移量数组
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset),     // 左上
        vec2( 0.0f,    offset),     // 正上
        vec2( offset,  offset),     // 右上
        vec2(-offset,  0.0f),       // 左
        vec2( 0.0f,    0.0f),       // 中
        vec2( offset,  0.0f),       // 右
        vec2(-offset, -offset),     // 左下
        vec2( 0.0f,   -offset),     // 正下
        vec2( offset, -offset)      // 右下
    );
    // 3x3 锐化(Sharpen)核（卷积矩阵）
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );
    // 颜色采样数组
    vec3 sampleTex[9];
    // 循环对顶点偏移数组进行采样
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(inTexture, inTexCoords.st + offsets[i]));
    }
    vec3 result = vec3(0.0);
    // 对采样的纹理值乘以加权的核值，并将结果累加变成一个值（当做当前顶点新的纹理颜色值）
    for(int i = 0; i < 9; i++)
    {
        result += sampleTex[i] * kernel[i];
    }
    
    return result;
}

/* 模糊处理 */
vec3 blur(sampler2D inTexture, vec2 inTexCoords)
{
    // 针对 3x3 核的偏移量数组
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset),     // 左上
        vec2( 0.0f,    offset),     // 正上
        vec2( offset,  offset),     // 右上
        vec2(-offset,  0.0f),       // 左
        vec2( 0.0f,    0.0f),       // 中
        vec2( offset,  0.0f),       // 右
        vec2(-offset, -offset),     // 左下
        vec2( 0.0f,   -offset),     // 正下
        vec2( offset, -offset)      // 右下
    );
    // 3x3 模糊(Blur)核（卷积矩阵）
    float kernel[9] = float[](
        1.0/16, 2.0/16, 1.0/16,
        2.0/16, 4.0/16, 2.0/16,
        1.0/16, 2.0/16, 1.0/16
    );
    // 颜色采样数组
    vec3 sampleTex[9];
    // 循环对顶点偏移数组进行采样
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(inTexture, inTexCoords.st + offsets[i]));
    }
    vec3 result = vec3(0.0);
    // 对采样的纹理值乘以加权的核值，并将结果累加变成一个值（当做当前顶点新的纹理颜色值）
    for(int i = 0; i < 9; i++)
    {
        result += sampleTex[i] * kernel[i];
    }
    
    return result;
}

/* 边缘检测 */
vec3 edgeDetection(sampler2D inTexture, vec2 inTexCoords)
{
    // 针对 3x3 核的偏移量数组
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset),     // 左上
        vec2( 0.0f,    offset),     // 正上
        vec2( offset,  offset),     // 右上
        vec2(-offset,  0.0f),       // 左
        vec2( 0.0f,    0.0f),       // 中
        vec2( offset,  0.0f),       // 右
        vec2(-offset, -offset),     // 左下
        vec2( 0.0f,   -offset),     // 正下
        vec2( offset, -offset)      // 右下
    );
    // 3x3 边缘检测(edgeDetection)核（卷积矩阵）
    float kernel[9] = float[](
        1,  1, 1,
        1, -8, 1,
        1,  1, 1
    );
    // 颜色采样数组
    vec3 sampleTex[9];
    // 循环对顶点偏移数组进行采样
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(inTexture, inTexCoords.st + offsets[i]));
    }
    vec3 result = vec3(0.0);
    // 对采样的纹理值乘以加权的核值，并将结果累加变成一个值（当做当前顶点新的纹理颜色值）
    for(int i = 0; i < 9; i++)
    {
        result += sampleTex[i] * kernel[i];
    }
    
    return result;
}

