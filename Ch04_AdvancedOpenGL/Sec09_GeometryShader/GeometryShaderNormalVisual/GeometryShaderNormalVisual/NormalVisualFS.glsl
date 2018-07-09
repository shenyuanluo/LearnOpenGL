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


#version 330 core   /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

out vec4 FragColor; /* 输出片段颜色 */

void main()
{
    FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}
