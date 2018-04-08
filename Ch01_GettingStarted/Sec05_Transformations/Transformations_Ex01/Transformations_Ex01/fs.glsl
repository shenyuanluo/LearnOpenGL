//
//  fs.glsl
//  Transformations_Ex01
//
//  Created by shenyuanluo on 2017/8/14.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 片段着色器
 */


#version 330 core   /* 指定GLSL版本3.3，匹配 OpenGL 版本 */


in vec3 vertexColor;    /* 输入，接收顶点颜色，从顶点着色器传来的输入变量（名称相同、类型相同） */
in vec2 texCoor;        /* 输入，接收文理坐标，从顶点着色器传来的输入变量（名称相同、类型相同） */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform sampler2D texture1; /* 纹理采样 1 */
uniform sampler2D texture2; /* 纹理采样 2 */

void main()
{
//    FragColor = texture(texture1, texCoor);   /* 纹理渲染 */
//    FragColor = texture(texture1, texCoor) * vec4(vertexColor, 1.0f);     /* 纹理与定点颜色混合 */
    /* 纹理组合：根据 mix 第三个参数进行线性插值计算，如果第三个值是 0.0，它会返回第一个输入；如果是 1.0，会返回第二个输入值；0.2 会返回 80% 的第一个输入颜色和 20% 的第二个输入颜色，即返回两个纹理的混合色 */
    FragColor = mix(texture(texture1, texCoor), texture(texture2, texCoor), 0.2);
}
