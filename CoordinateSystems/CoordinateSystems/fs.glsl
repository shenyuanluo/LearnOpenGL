//
//  fs.glsl
//  Shaders
//
//  Created by shenyuanluo on 2017/9/6.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#version 330 core           // 指定GLSL版本3.3

in vec2 texCoord;           // 接收，顶点纹理坐标

out vec4 fragColor;         // 输出，指定片段颜色

uniform sampler2D texture1;
uniform sampler2D texture2;


void main()
{
    // GLSL内建的mix函数需要接受两个值作为参数，并对它们根据第三个参数进行线性插值。如果第三个值是0.0，它会返回第一个输入；如果是1.0，会返回第二个输入值。0.2会返回80%的第一个输入颜色和20%的第二个输入颜色，即返回两个纹理的混合色。
    fragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.3);
}
