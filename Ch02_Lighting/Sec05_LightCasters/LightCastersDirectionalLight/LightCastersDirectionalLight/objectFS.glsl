//
//  objectFS.glsl
//  LightCastersDirectionalLight
//
//  Created by shenyuanluo on 2017/8/21.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘物体’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */

/* 材质属性 */
struct Material {
    /*
     移除环境光材质颜色向量，因为环境光颜色在几乎所有情况下都等于漫反射颜色
    vec3 ambient;       // 环境光照·颜色
    */
    sampler2D diffuse;  /* 漫反射贴图 */
    sampler2D specular; /* 镜面光贴图 */
    float shininess;    /* 反光度 */
};

/* 光照属性 */
struct Light {
    /*平行光是：直接使用光的 direction 向量而不是通过 direction 来计算 lightDir 向量。*/
    vec3 direction;     /* 光照方向向量（模拟：定向光/平行光）*/
    vec3 ambient;       /* 环境光照·强度 */
    vec3 diffuse;       /* 漫反射光照·强度 */
    vec3 specular;      /* 镜面光照·强度 */
};

in vec3 FragPos;        /* 输入，接收片段位置向量 */
in vec3 Normal;         /* 输入，顶点接收法向量 */
in vec2 TexCoords;      /* 输入，(漫反射)纹理坐标 */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform Material material;  /* 材质属性变量 */
uniform Light light;        /* 光照属性变量 */

uniform vec3 viewerPos;     /* 观察者位置向量 */

void main()
{
    /* 环境光照 */
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    /* 漫反射光照 */
    vec3 norm     = normalize(Normal);
    /* 对 light.direction 向量取反。
     因为目前使用的光照计算需求一个从片段至光源的光线方向，
     但更习惯定义定向光为一个从光源出发的全局方向 */
    vec3 lightDir = normalize(-light.direction);
    float diff    = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
    /* 镜面光照 */
    vec3 viewDir    = normalize(viewerPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular   = light.specular * (spec * vec3(texture(material.specular, TexCoords)));
    
    /* 最终颜色 */
    vec3 result     = ambient + diffuse + specular;
    
    FragColor = vec4(result, 1.0);
}
