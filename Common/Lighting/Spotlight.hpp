//
//  Spotlight.hpp
//  
//
//  Created by shenyuanluo on 2017/8/22.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Spotlight_hpp
#define Spotlight_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Shader.hpp"


/* 聚光源属性
struct SpotLight {
    vec3 position;      // 光源位置
    vec3 direction;     // 光照方向向量
    float cutOff;       // 内切光角·余弦
    float outerCutOff;  // 外切光角·余弦
    float constant;     // 光强度衰减公式·常数项
    float linear;       // 光强度衰减公式·一次项
    float quadratic;    // 光强度衰减公式·二次项
    vec3 ambient;       // 环境光照·强度
    vec3 diffuse;       // 漫反射光照·强度
    vec3 specular;      // 镜面光照·强度
};
*/


class Spotlight
{
private:
    Shader m_shader;                                    /* 着色器对象 */
    const std::string m_spotLight;                      /* 聚光源变量 */
    const std::string m_position    = "position";       /* 光源位置(GLSL)变量 */
    const std::string m_direction   = "direction";      /* 光照方向(GLSL)变量 */
    const std::string m_cutOff      = "cutOff";         /* 内切光角·余弦(GLSL)变量 */
    const std::string m_outerCutOff = "outerCutOff";    /* 外切光角·余弦(GLSL)变量 */
    const std::string m_constant    = "constant";       /* 光强度衰减公式·常数项(GLSL)变量 */
    const std::string m_linear      = "linear";         /* 光强度衰减公式·一次项(GLSL)变量 */
    const std::string m_quadratic   = "quadratic";      /* 光强度衰减公式·二次项(GLSL)变量 */
    const std::string m_ambient     = "ambient";        /* 环境光照·强度(GLSL)变量 */
    const std::string m_diffuse     = "diffuse";        /* 漫反射光照·强度(GLSL)变量 */
    const std::string m_specular    = "specular";       /* 镜面光照·强度(GLSL)变量 */
    
public:
    Spotlight(Shader &shader, const std::string &spotLight);
    
    ~Spotlight();
    
    /**
     设置聚光源位置
     */
    void setPosition(glm::vec3 position);
    
    void setPosition(GLfloat posX, GLfloat posY, GLfloat posZ);
    
    /**
     设置聚光方向
     */
    void setDirection(glm::vec3 direction);
    
    void setDirection(GLfloat dirX, GLfloat dirY, GLfloat dirZ);
    
    /**
     设置内切光角·余弦

     @param cutOff 内切光角·余弦
     */
    void setCutOff(GLfloat cutOff);

    /**
     设置外切光角·余弦
     
     @param outerCutOff 外切光角·余弦
     */
    void setOuterCutOff(GLfloat outerCutOff);
    
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

#endif /* Spotlight_hpp */
