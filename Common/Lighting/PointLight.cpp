//
//  PointLight.cpp
//  
//
//  Created by shenyuanluo on 2017/8/22.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "PointLight.hpp"

#pragma mark - Public
#pragma mark -- 构造函数
PointLight::PointLight(Shader &shader, const std::string &pointLight) : m_shader(shader), m_pointLight(pointLight)
{
    
}

#pragma mark -- 析构函数
PointLight::~PointLight()
{
    
}

#pragma mark -- 设置点光源位置
void PointLight::setPosition(glm::vec3 position)
{
    m_shader.setUniformVec3(m_pointLight + "." + m_position, position);
}

void PointLight::setPosition(GLfloat posX, GLfloat posY, GLfloat posZ)
{
    m_shader.setUniformVec3(m_pointLight + "." + m_position, posX, posY, posZ);
}

#pragma mark -- 设置光强度衰减公式·常数项
void PointLight::setConstant(GLfloat constant)
{
    m_shader.setUniformFloat(m_pointLight + "." + m_constant, constant);
}

#pragma mark -- 设置光强度衰减公式·一次项
void PointLight::setLinear(GLfloat linear)
{
    m_shader.setUniformFloat(m_pointLight + "." + m_linear, linear);
}

#pragma mark -- 设置光强度衰减公式·二次项
void PointLight::setQuadratic(GLfloat quadratic)
{
    m_shader.setUniformFloat(m_pointLight + "." + m_quadratic, quadratic);
}

#pragma mark -- 设置环境光照·强度
void PointLight::setAmbient(glm::vec3 ambient)
{
    m_shader.setUniformVec3(m_pointLight + "." + m_ambient,  ambient);
}

void PointLight::setAmbient(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB)
{
    m_shader.setUniformVec3(m_pointLight + "." + m_ambient,  ambientR, ambientG, ambientB);
}

#pragma mark -- 设置漫反射·强度
void PointLight::setDiffuse(glm::vec3 diffuse)
{
    m_shader.setUniformVec3(m_pointLight + "." + m_diffuse,  diffuse);
}

void PointLight::setDiffuse(GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB)
{
    m_shader.setUniformVec3(m_pointLight + "." + m_diffuse,  diffuseR, diffuseG, diffuseB);
}

#pragma mark -- 设置镜面光·强度
void PointLight::setSpecular(glm::vec3 specular)
{
    m_shader.setUniformVec3(m_pointLight + "." + m_specular, specular);
}

void PointLight::setSpecular(GLfloat specularR, GLfloat specularG, GLfloat specularB)
{
    m_shader.setUniformVec3(m_pointLight + "." + m_specular, specularR, specularG, specularB);
}


#pragma mark - Private
