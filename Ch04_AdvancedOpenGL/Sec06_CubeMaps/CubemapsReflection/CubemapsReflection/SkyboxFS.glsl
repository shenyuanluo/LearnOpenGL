//
//  SkyboxFS.glsl
//  CubemapsReflection
//
//  Created by shenyuanluo on 2017/9/6.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘天空盒’片段着色器
 */


#version 330 core   /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

in vec3 TexCoords;  /* 输入，纹理坐标（注意是 3D 类型） */

out vec4 FragColor; /* 输出，指定片段颜色 */

uniform samplerCube skybox; /* （立方体）3D 纹理采样 */

void main()
{
    FragColor = texture(skybox, TexCoords);
}
