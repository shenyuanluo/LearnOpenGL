//
//  modeLoadingFS.glsl
//  ModelAddLighting
//
//  Created by shenyuanluo on 2017/8/24.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ‘Nanosuit’片段着色器
 */


#version 330 core       /* 指定GLSL版本3.3，匹配 OpenGL 版本 */
#define POINT_LIGHT_COUNT 4    /* 点光源数量 */

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

/* 定向光属性 */
struct DirLight {
    vec3 direction;     /* 光照方向向量 */
    
    vec3 ambient;       /* 环境光照·强度 */
    vec3 diffuse;       /* 漫反射光照·强度 */
    vec3 specular;      /* 镜面光照·强度 */
};

/* 点光源属性 */
struct PointLight {
    vec3 position;      /* 光源位置 */
    
    float constant;     /* 光强度衰减公式·常数项 */
    float linear;       /* 光强度衰减公式·一次项 */
    float quadratic;    /* 光强度衰减公式·二次项 */
    
    vec3 ambient;       /* 环境光照·强度 */
    vec3 diffuse;       /* 漫反射光照·强度 */
    vec3 specular;      /* 镜面光照·强度 */
};

/* 聚光源属性 */
struct SpotLight {
    vec3 position;      /* 光源位置 */
    vec3 direction;     /* 光照方向向量*/
    float cutOff;       /* 内切光角·余弦 */
    float outerCutOff;  /* 外切光角·余弦 */
    
    float constant;     /* 光强度衰减公式·常数项 */
    float linear;       /* 光强度衰减公式·一次项 */
    float quadratic;    /* 光强度衰减公式·二次项 */
    
    vec3 ambient;       /* 环境光照·强度 */
    vec3 diffuse;       /* 漫反射光照·强度 */
    vec3 specular;      /* 镜面光照·强度 */
};

in vec3 FragPos;        /* 输入，接收片段位置向量 */
in vec3 Normal;         /* 输入，顶点接收法向量 */
in vec2 TexCoords;      /* 输入，纹理坐标 */

out vec4 FragColor;     /* 输出，指定片段颜色 */

uniform Material material;  /* 材质属性变量 */

uniform DirLight dirLight;  /* 定向光变量 */
uniform PointLight pointLights[POINT_LIGHT_COUNT]; /* 点光源数组 */
uniform SpotLight spotLight;    /* 聚光源变量 */

uniform vec3 viewerPos;     /* 观察者位置向量 */

/**
 计算定向光颜色
 
 @param light 定向光
 @param normal 顶点法向量
 @param viewDir 观察者方向向量
 @return 定向光颜色
 */
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

/**
 计算点光源颜色
 
 @param light 点光源
 @param normal 顶点法向量
 @param viewDir 观察者方向向量
 @param fragPos 顶点片段位置向量
 @return 点光源颜色
 */
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos);


/**
 计算聚光源颜色
 
 @param light 聚光源
 @param normal 顶点法向量
 @param viewDir 观察者方向向量
 @param fragPos 顶点片段位置向量
 @return 聚光源颜色
 */
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos);

void main()
{
    // 属性
    vec3 norm    = normalize(Normal);
    vec3 viewDir = normalize(viewerPos - FragPos);
    vec3 result;
    
    // 第一阶段：定向光照
    result = CalcDirLight(dirLight, norm, viewDir);
    // 第二阶段：点光源
    for(int i = 0; i < POINT_LIGHT_COUNT; i++)
    {
        result += CalcPointLight(pointLights[i], norm, viewDir, FragPos);
    }
    // 第三阶段：聚光
    result += CalcSpotLight(spotLight, norm, viewDir, FragPos);
    
    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    /* ========== 环境光照 ========== */
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    
    /* ========== 漫反射 ========== */
    vec3 lightDir = normalize(-light.direction);        // 光照方向(取反：光源发出的全局方向)
    float diff    = max(dot(normal, lightDir), 0.0);    // 漫反射影响
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
    
    /* ========== 镜面光 ========== */
    vec3 reflectDir = reflect(-lightDir, normal);       // 反射光照方向
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  // 镜面光影响
    vec3 specular   = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    
    /* 最终定向光颜色 */
    vec3 result = ambient + diffuse + specular;
    
    return result;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
    /* ========== 环境光照 ========== */
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    
    /* ========== 漫反射 ========== */
    vec3 lightDir = normalize(light.position - fragPos);        // 光照方向
    float diff    = max(dot(normal, lightDir), 0.0);    // 漫反射影响
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
    
    /* ========== 镜面光 ========== */
    vec3 reflectDir = reflect(-lightDir, normal);       // 反射光照方向
    float spec      = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  // 镜面光影响
    vec3 specular   = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    
    /* ========== 衰减 ========== */
    /* 距离 */
    float lDistance = length(light.position - fragPos);
    /* 衰减 */
    float attenuation = 1.0 / (light.constant + light.linear * lDistance +
                               light.quadratic * (lDistance * lDistance));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    
    
    /* 最终颜色 */
    vec3 result = ambient + diffuse + specular;
    
    return result;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
    /* ========== 环境光照 ========== */
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    
    /* ========== 漫反射 ========== */
    vec3 lightDir = normalize(light.position - fragPos);    // 光照方向
    float diff    = max(dot(lightDir, normal), 0.0);        // 漫反射影响
    vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
    
    /* ========== 镜面光 ========== */
    vec3 reflectDir = reflect(-lightDir, normal);   // 反射光照
    float spec      = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);  // 经面光影响
    vec3 specular   = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    
    /* ========== 衰减 ========== */
    /* 距离 */
    float lDistance = length(light.position - fragPos);
    /* 衰减 */
    float attenuation = 1.0 / (light.constant + light.linear * lDistance +
                               light.quadratic * (lDistance * lDistance));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    
    
    /* ========== 聚光圈边平滑 ========== */
    vec3 spotDir  = normalize(-light.direction);        // 聚光灯方向
    float theta   = dot(lightDir, spotDir);             // 夹角(θ)·余弦
    float epsilon = light.cutOff - light.outerCutOff;   // ϵ
    // 聚光强度（clamp 函数 第一个参数 约束在 第二个参数 到 第三个参数 之间）
    float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0f, 1.0f);
    /* 将不对环境光做出影响，让它总是能有一点光
     ambient  *= intensity; */
    diffuse  *= intensity;
    specular *= intensity;
    
    
    /* 最终颜色 */
    vec3 result = ambient + diffuse + specular;
    
    return result;
}
