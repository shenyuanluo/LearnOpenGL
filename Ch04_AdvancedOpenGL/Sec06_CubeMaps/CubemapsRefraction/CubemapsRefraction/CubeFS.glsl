//
//  CubeFS.glsl
//  CubemapsRefraction
//
//  Created by shenyuanluo on 2017/9/6.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘箱子’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

in vec3 Normal;         /* 顶点法向量 */
in vec3 Position;       /* 顶点位置向量 */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform vec3 cameraPos;    /* 摄像机位置向量 */

uniform samplerCube skybox;     /* 天空盒子纹理 */


void main()
{
    // (折射率)比值  水     玻璃
    float ratio = 1.00 / 1.52;
    /* 观察方向向量 */
    vec3 camDir = normalize(Position - cameraPos);
    /* 观察方向的折射向量 */
    vec3 camDirRefract = refract(camDir, normalize(Normal), ratio);
    /* 使用折射向量从天空盒立方体贴图中采样 */
    FragColor = vec4(texture(skybox, camDirRefract).rgb, 1.0);
}
