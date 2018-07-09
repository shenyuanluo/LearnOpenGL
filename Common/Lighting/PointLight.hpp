//
//  PointLight.hpp
//  
//
//  Created by shenyuanluo on 2017/8/22.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Shader.hpp"

/* 点光源属性
struct PointLight {
    vec3 position;      // 光源位置
    float constant;     // 光强度衰减公式·常数项
    float linear;       // 光强度衰减公式·一次项
    float quadratic;    // 光强度衰减公式·二次项
    vec3 ambient;       // 环境光照·强度
    vec3 diffuse;       // 漫反射光照·强度
    vec3 specular;      // 镜面光照·强度
};
*/

/* 点光灯类 */
class PointLight
{
private:
    Shader m_shader;                                /* 着色器对象 */
    const std::string m_pointLight;                 /* 点光源变量 */
    const std::string m_position  = "position";     /* 光源位置(GLSL)变量 */
    const std::string m_constant  = "constant";     /* 光强度衰减公式·常数项(GLSL)变量 */
    const std::string m_linear    = "linear";       /* 光强度衰减公式·一次项(GLSL)变量 */
    const std::string m_quadratic = "quadratic";    /* 光强度衰减公式·二次项(GLSL)变量 */
    const std::string m_ambient   = "ambient";      /* 环境光照·强度(GLSL)变量 */
    const std::string m_diffuse   = "diffuse";      /* 漫反射光照·强度(GLSL)变量 */
    const std::string m_specular  = "specular";     /* 镜面光照·强度(GLSL)变量 */
    
public:
    PointLight(Shader &shader, const std::string &pointLight);
    
    ~PointLight();
    
    /**
     设置点光源位置
     */
    void setPosition(glm::vec3 position);
    
    void setPosition(GLfloat posX, GLfloat posY, GLfloat posZ);
    
    /**
     设置光强度衰减公式·常数项
     */
    void setConstant(GLfloat constant);
    
    /**
     设置光强度衰减公式·一次项
     */
    void setLinear(GLfloat linear);
    
    /**
     设置光强度衰减公式·二次项
     */
    void setQuadratic(GLfloat quadratic);
    
    /**
     设置环境光照·强度
     */
    void setAmbient(glm::vec3 ambient);
    
    void setAmbient(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB);
    
    /**
     设置漫反射·强度
     */
    void setDiffuse(glm::vec3 diffuse);
    
    void setDiffuse(GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB);
    
    /**
     设置镜面光·强度
     */
    void setSpecular(glm::vec3 specular);
    
    void setSpecular(GLfloat specularR, GLfloat specularG, GLfloat specularB);
};

#endif /* PointLight_hpp */
