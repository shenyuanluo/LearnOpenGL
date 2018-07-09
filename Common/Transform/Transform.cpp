//
//  Transform.cpp
//  
//
//  Created by shenyuanluo on 2017/8/14.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Transform.hpp"


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

void Transform::translate(glm::vec3 transVec)
{
    m_transformMat = glm::translate(m_transformMat, transVec);
}

#pragma mark -- 旋转（矩阵）操作
void Transform::rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    m_transformMat = glm::rotate(m_transformMat, angle, glm::vec3(x, y, z));
}

void Transform::rotate(GLfloat angle, glm::vec3 rotateVec)
{
    m_transformMat = glm::rotate(m_transformMat, angle, rotateVec);
}

#pragma mark -- 缩放（矩阵）操作
void Transform::scale(GLfloat x, GLfloat y, GLfloat z)
{
    m_transformMat = glm::scale(m_transformMat, glm::vec3(x, y, z));
}

void Transform::scale(glm::vec3 scaleVec)
{
    m_transformMat = glm::scale(m_transformMat, scaleVec);
}

#pragma mark -- ’逆矩阵‘操作
void Transform::inverse()
{
    m_transformMat = glm::inverse(m_transformMat);
}

#pragma mark -- ’转置矩阵‘操作
void Transform::transpose()
{
    m_transformMat = glm::transpose(m_transformMat);
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
GLfloat Transform::radianWithDegree(GLfloat degree) const
{
    return glm::radians(degree);
}

#pragma mark -- 使用变换矩阵
GLfloat* Transform::use()
{
//    return &m_transformMat[0][0];           /* 使用变换矩阵数组第一个元素地址作为指针传值 */
    return glm::value_ptr(m_transformMat);
}

#pragma mark -- 强制转换为左上角 3x3 矩阵
glm::mat3 Transform::convertMat3() const
{
    glm::mat3 transMat3 = glm::mat3(m_transformMat);
    return transMat3;
    /* 转换成 GLfloat* 会出错，原因未知 */
//    return glm::value_ptr(transMat3);
}

#pragma mark -- 重置为单位矩阵
void Transform::reset()
{
    m_transformMat = glm::mat4();
}
