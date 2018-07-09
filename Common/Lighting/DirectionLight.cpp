//
//  DirectionLight.cpp
//  
//
//  Created by shenyuanluo on 2017/8/22.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "DirectionLight.hpp"

#pragma mark - Public
#pragma mark -- 构造函数
DirectionLight::DirectionLight(Shader &shader, const std::string &dirLight) : m_shader(shader), m_dirLight(dirLight)
{
    
}

#pragma mark -- 析构函数
DirectionLight::~DirectionLight()
{
    
}

#pragma mark -- 设置光照方向
void DirectionLight::setDirection(glm::vec3 direction)
{
    m_shader.setUniformVec3(m_dirLight + "." + m_direction, direction);
}

void DirectionLight::setDirection(GLfloat dirX, GLfloat dirY, GLfloat dirZ)
{
    m_shader.setUniformVec3(m_dirLight + "." + m_direction, dirX, dirY, dirZ);
}

#pragma mark -- 设置环境光照·强度
void DirectionLight::setAmbient(glm::vec3 ambient)
{
    m_shader.setUniformVec3(m_dirLight + "." + m_ambient,  ambient);
}

void DirectionLight::setAmbient(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB)
{
    m_shader.setUniformVec3(m_dirLight + "." + m_ambient,  ambientR, ambientG, ambientB);
}

#pragma mark -- 设置漫反射·强度
void DirectionLight::setDiffuse(glm::vec3 diffuse)
{
    m_shader.setUniformVec3(m_dirLight + "." + m_diffuse,  diffuse);
}

void DirectionLight::setDiffuse(GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB)
{
    m_shader.setUniformVec3(m_dirLight + "." + m_diffuse,  diffuseR, diffuseG, diffuseB);
}

#pragma mark -- 设置镜面光·强度
void DirectionLight::setSpecular(glm::vec3 specular)
{
    m_shader.setUniformVec3(m_dirLight + "." + m_specular, specular);
}

void DirectionLight::setSpecular(GLfloat specularR, GLfloat specularG, GLfloat specularB)
{
    m_shader.setUniformVec3(m_dirLight + "." + m_specular, specularR, specularG, specularB);
}
