//
//  DirectionLight.hpp
//  
//
//  Created by shenyuanluo on 2017/8/22.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef DirectionLight_hpp
#define DirectionLight_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Shader.hpp"


/* 定向光属性
struct DirLight {
    vec3 direction;     // 光照方向向量
    vec3 ambient;       // 环境光照·强度
    vec3 diffuse;       // 漫反射光照·强度
    vec3 specular;      // 镜面光照·强度
};
*/


/* 定向光类 */
class DirectionLight
{
private:
    Shader m_shader;                                /* 着色器对象 */
    const std::string m_dirLight;                   /* 定向光变量 */
    const std::string m_direction = "direction";    /* 光照方向(GLSL)变量 */
    const std::string m_ambient   = "ambient";      /* 环境光照·强度(GLSL)变量 */
    const std::string m_diffuse   = "diffuse";      /* 漫反射光照·强度(GLSL)变量 */
    const std::string m_specular  = "specular";     /* 镜面光照·强度(GLSL)变量 */
    
public:
    
    DirectionLight(Shader &shader, const std::string &dirLight);
    
    ~DirectionLight();
    
    /**
     设置光照方向
     */
    void setDirection(glm::vec3 direction);
    
    void setDirection(GLfloat dirX, GLfloat dirY, GLfloat dirZ);
    
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

#endif /* DirectionLight_hpp */
