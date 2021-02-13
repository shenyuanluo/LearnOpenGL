//
//  objectFS.glsl
//  LightCastersPointLight
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
    vec3 position;      /* 光源位置 */
    float constant;     /* 光强度衰减公式·常数项 */
    float linear;       /* 光强度衰减公式·一次项 */
    float quadratic;    /* 光强度衰减公式·二次项 */
    
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
    /* ============= 光强度衰减计算 ============= */
    /* 距离 */
    float lDistance = length(light.position - FragPos);
    /* 衰减 */
    float attenuation = 1.0 / (light.constant + light.linear * lDistance +
                               light.quadratic * (lDistance * lDistance));
    /* 环境光照 */
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    /* 漫反射光照 */
    vec3 norm     = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff    = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
    /* 镜面光照 */
    vec3 viewDir    = normalize(viewerPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular   = light.specular * (spec * vec3(texture(material.specular, TexCoords)));
    
    /* 计算衰减 */
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    
    /* 最终颜色 */
    vec3 result = ambient + diffuse + specular;
    
    FragColor = vec4(result, 1.0);
}
