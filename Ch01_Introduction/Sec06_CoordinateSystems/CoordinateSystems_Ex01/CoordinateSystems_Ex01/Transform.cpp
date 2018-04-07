//
//  Transform.cpp
//  CoordinateSystems_Ex01
//
//  Created by shenyuanluo on 2017/8/15.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#pragma mark - Public
#pragma mark -- 构造函数
Transform::Transform()
{
    reset();
}

#pragma mark -- 析构函数
Transform::~Transform()
{
    reset();
}

#pragma mark -- 平移（矩阵）操作
void Transform::translate(GLfloat x, GLfloat y, GLfloat z)
{
    m_transformMat = glm::translate(m_transformMat, glm::vec3(x, y, z));
}

#pragma mark -- 旋转（矩阵）操作
void Transform::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    m_transformMat = glm::rotate(m_transformMat, angle, glm::vec3(x, y, z));
}

#pragma mark -- 缩放（矩阵）操作
void Transform::scale(GLfloat x, GLfloat y, GLfloat z)
{
    m_transformMat = glm::scale(m_transformMat, glm::vec3(x, y, z));
}

#pragma mark -- 创建（透视）投影矩阵
void Transform::perspective(GLfloat angle, GLfloat width, GLfloat height, GLfloat nearPlane, GLfloat farPlane)
{
    m_transformMat = glm::perspective(angle, width/height, nearPlane, farPlane);
}

#pragma mark -- 创建（正射）投影矩阵
void Transform::orthographic(GLfloat left, GLfloat right, GLfloat top, GLfloat bottom, GLfloat nearPlane, GLfloat farPlane)
{
    m_transformMat = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
}

#pragma mark -- 角度制转弧度制
GLfloat Transform::radianWithDegree(GLfloat degree)
{
    return glm::radians(degree);
}

#pragma mark -- 使用变换矩阵
GLfloat* Transform::use()
{
//    return &m_transformMat[0][0];           /* 使用变换矩阵数组第一个元素地址作为指针传值 */
    return glm::value_ptr(m_transformMat);
}

#pragma mark -- 重置为单位矩阵
void Transform::reset()
{
    m_transformMat = glm::mat4();
}
