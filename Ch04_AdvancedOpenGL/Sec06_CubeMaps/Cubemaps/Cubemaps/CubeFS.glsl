//
//  CubeFS.glsl
//  Cubemaps
//
//  Created by shenyuanluo on 2017/9/6.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘箱子’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

in vec2 TexCoords;      /* 输入，(2D)纹理坐标*/

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform sampler2D cubeSampler;      /* (2D)箱子纹理采样器 */
uniform sampler2D emojiSampler;     /* (2D)Emoji 表情纹理采样器 */

void main()
{
    FragColor = mix(texture(cubeSampler, TexCoords), texture(emojiSampler, TexCoords), 0.3);
}
