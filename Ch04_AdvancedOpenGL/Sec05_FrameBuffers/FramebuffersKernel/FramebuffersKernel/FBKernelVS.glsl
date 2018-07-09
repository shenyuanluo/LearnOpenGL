//
//  FBKernelVS.glsl
//  FramebuffersKernel
//
//  Created by shenyuanluo on 2017/9/5.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘帧缓冲（核）’顶点着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */
layout (location = 0) in vec3 aPos;         /* 顶点位置变量的属性位置值为：0 */
layout (location = 1) in vec2 aTexCoords;   /* 顶点颜色变量的属性位置值为：1 */

out vec2 TexCoords;      /* 输出，指定文理坐标（传递给片段着色器） */

/* 将不会包含矩阵变换，因为将提供的是标准化设备坐标的顶点坐标 */

void main()
{
    // 因为屏幕四边形使用的是 NDC，所以坐标只有 x、y 分量
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    TexCoords = aTexCoords;
}

