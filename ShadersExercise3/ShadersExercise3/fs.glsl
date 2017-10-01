//
//  fs.glsl
//  Shaders
//
//  Created by shenyuanluo on 2017/9/6.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#version 330 core       // 指定GLSL版本3.3
in vec3 customColor;    // 接收，顶点颜色数据
out vec4 fragColor;     // 输出，指定片段颜色
void main()
{
    fragColor = vec4(customColor, 1.0);
}
