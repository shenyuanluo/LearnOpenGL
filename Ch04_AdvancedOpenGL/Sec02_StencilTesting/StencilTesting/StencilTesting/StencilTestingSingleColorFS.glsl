//
//  StencilTestingSingleColorFS.glsl
//  StencilTesting
//
//  Created by shenyuanluo on 2017/9/2.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘模板测试·轮廓’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

out vec4 FragColor;     /* 输出，指定片段颜色 */

void main()
{
    FragColor = vec4(0.4, 0.28, 0.26, 1.0);;
}
