//
//  DepthTestingFS.glsl
//  DepthTesting
//
//  Created by shenyuanluo on 2017/9/1.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘深度测试’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

in vec2 TexCoords;      /* 输入，接收顶点颜色，从顶点着色器传来的输入变量（名称相同、类型相同） */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform sampler2D texture1; /* 纹理采样 1 */

float near = 0.1;       /* 平截头体·近平面值 */
float far  = 100.0;     /* 平截头体·远平面值 */

/**
 线性深度值转换
 
 @param depth 非线性深度值（默认）
 @return 线性深度值
 */
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;    /* 转换成 NDC */
    return (2.0 * near * far) / (far + near - z * (far - near));
}


void main()
{
    // 场景演示
    FragColor = texture(texture1, TexCoords);
    
    // 非线性深度值演示（默认）
//    FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
    
    // 线性深度值演示
//    float depth = LinearizeDepth(gl_FragCoord.z) / far; // 为了演示除以 far
//    FragColor = vec4(vec3(depth), 1.0);
}
