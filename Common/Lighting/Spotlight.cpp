//
//  Spotlight.cpp
//  
//
//  Created by shenyuanluo on 2017/8/22.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Spotlight.hpp"


#pragma mark - Public
#pragma mark -- 构造函数
Spotlight::Spotlight(Shader &shader, const std::string &spotLight) : m_shader(shader), m_spotLight(spotLight)
{
    
}

#pragma mark -- 析构函数
Spotlight::~Spotlight()
{
    
}

#pragma mark -- 设置聚光源位置
void Spotlight::setPosition(glm::vec3 position)
{
    m_shader.setUniformVec3(m_spotLight + "." + m_position, position);
}

void Spotlight::setPosition(GLfloat posX, GLfloat posY, GLfloat posZ)
{
    m_shader.setUniformVec3(m_spotLight + "." + m_position, posX, posY, posZ);
}

#pragma mark -- 设置聚光方向
void Spotlight::setDirection(glm::vec3 direction)
{
    m_shader.setUniformVec3(m_spotLight + "." + m_direction, direction);
}

void Spotlight::setDirection(GLfloat dirX, GLfloat dirY, GLfloat dirZ)
{
    m_shader.setUniformVec3(m_spotLight + "." + m_direction, dirX, dirY, dirZ);
}

#pragma mark -- 设置内切光角·余弦
void Spotlight::setCutOff(GLfloat cutOff)
{
    m_shader.setUniformFloat(m_spotLight + "." + m_cutOff, cutOff);
}

#pragma mark -- 设置外切光角·余弦
void Spotlight::setOuterCutOff(GLfloat outerCutOff)
{
    m_shader.setUniformFloat(m_spotLight + "." + m_outerCutOff, outerCutOff);
}

#pragma mark -- 设置光强度衰减公式·常数项
void Spotlight::setConstant(GLfloat constant)
{
    m_shader.setUniformFloat(m_spotLight + "." + m_constant, constant);
}

#pragma mark -- 设置光强度衰减公式·一次项
void Spotlight::setLinear(GLfloat linear)
{
    m_shader.setUniformFloat(m_spotLight + "." + m_linear, linear);
}

#pragma mark -- 设置光强度衰减公式·二次项
void Spotlight::setQuadratic(GLfloat quadratic)
{
    m_shader.setUniformFloat(m_spotLight + "." + m_quadratic, quadratic);
}

#pragma mark -- 设置环境光照·强度
void Spotlight::setAmbient(glm::vec3 ambient)
{
    m_shader.setUniformVec3(m_spotLight + "." + m_ambient,  ambient);
}

void Spotlight::setAmbient(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB)
{
    m_shader.setUniformVec3(m_spotLight + "." + m_ambient,  ambientR, ambientG, ambientB);
}

#pragma mark -- 设置漫反射·强度
void Spotlight::setDiffuse(glm::vec3 diffuse)
{
    m_shader.setUniformVec3(m_spotLight + "." + m_diffuse,  diffuse);
}

void Spotlight::setDiffuse(GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB)
{
    m_shader.setUniformVec3(m_spotLight + "." + m_diffuse,  diffuseR, diffuseG, diffuseB);
}

#pragma mark -- 设置镜面光·强度
void Spotlight::setSpecular(glm::vec3 specular)
{
    m_shader.setUniformVec3(m_spotLight + "." + m_specular, specular);
}

void Spotlight::setSpecular(GLfloat specularR, GLfloat specularG, GLfloat specularB)
{
    m_shader.setUniformVec3(m_spotLight + "." + m_specular, specularR, specularG, specularB);
}
