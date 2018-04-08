//
//  Camera.cpp
//  Camera_Ex01
//
//  Created by shenyuanluo on 2017/8/16.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma mark - Public
#pragma mark -- 构造函数1
Camera::Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch) : m_camFront(glm::vec3(0.0f, 0.0f, -1.0f)), m_moveSpeed(kMoveSpeed), m_mouseSensitivity(kSensitivity), m_zoom(kZoom)
{
    m_camPos = position;
    m_wordUp = worldUp;
    m_yaw    = yaw;
    m_pitch  = pitch;
    
    updateCameraVectors();
}

#pragma mark -- 构造函数2
Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat worldUpX, GLfloat worldUpY, GLfloat worldUpZ, GLfloat yaw, GLfloat pitch) : m_camFront(glm::vec3(0.0f, 0.0f, -1.0f)), m_moveSpeed(kMoveSpeed), m_mouseSensitivity(kSensitivity), m_zoom(kZoom)
{
    m_camPos = glm::vec3(posX, posY, posZ);
    m_wordUp = glm::vec3(worldUpX, worldUpY, worldUpZ);
    m_yaw    = yaw;
    m_pitch  = pitch;
    
    updateCameraVectors();
}

#pragma mark -- 使用摄像机（观察矩阵）
GLfloat* Camera::use()
{
    m_viewMat = glm::lookAt(m_camPos, m_camPos + m_camFront, m_camUp);
    return glm::value_ptr(m_viewMat);
}

#pragma mark -- 获取视野
GLfloat Camera::fov()
{
    return glm::radians(m_zoom);
}

#pragma mark -- 键盘移动
void Camera::keyboardMove(MoveDirection direction, GLfloat dealTime)
{
    /* 平均移动速度 */
    GLfloat velocity = m_moveSpeed * dealTime;
    switch (direction)
    {
        case Move_forward:  /* 向前移动 */
            m_camPos += m_camFront * velocity;
            break;
            
        case Move_backward: /* 向后移动 */
            m_camPos -= m_camFront * velocity;
            break;
            
        case Move_left:     /* 向左移动 */
            m_camPos -= m_camRight * velocity;
            break;
            
        case Move_right:    /* 向右移动 */
            m_camPos += m_camRight * velocity;
            break;
            
        default:
            break;
    }
//    m_camPos.y = 0.0f;  /* FPS摄像机（限制在 xz 平面） */
}

#pragma mark -- 鼠标移动
void Camera::mouseMove(GLfloat offsetX, GLfloat offsetY, GLboolean constrainPitch)
{
    offsetX *= m_mouseSensitivity;
    offsetY *= m_mouseSensitivity;
    
#ifdef __APPLE__    /* Mac OS 鼠标移动方向默认跟鼠标一致 */
    m_yaw   -= offsetX;
    m_pitch -= offsetY;
#else
    m_yaw   += offsetX;
    m_pitch += offsetY;
#endif
    
    if (constrainPitch)
    {
        /* 限制最大‘仰’角：89 度，因为在 90 度时视角会发生逆转 */
        if (89.0f <= m_pitch)
        {
            m_pitch = 89.0f;
        }
        /* 限制最大‘俯’角：-89 度，因为在 -90 度时视角会发生逆转 */
        if (-89.0f >= m_pitch)
        {
            m_pitch = -89.0f;
        }
    }
    
    updateCameraVectors();
}

#pragma mark -- 鼠标滚动动
void Camera::mouseScroll(GLfloat offsetY)
{
    if (1.0f <= m_zoom && kZoom >= m_zoom)
    {
        m_zoom -= offsetY;
    }
    if (1.0f >= m_zoom)
    {
        m_zoom = 1.0f;
    }
    if (kZoom <= m_zoom)
    {
        m_zoom = kZoom;
    }
}


#pragma mark - Private
#pragma mark -- 更新摄像机有关向量
void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
    front.y = sin(glm::radians(m_pitch));
    front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
    
    /* 更新摄像机 Z（方向向量） 轴 */
    m_camFront = glm::normalize(front);
    /* 更新摄像机 X（右向量） 轴 = 摄像机方向向量 x 世界上向量 */
    m_camRight = glm::normalize(glm::cross(m_camFront, m_wordUp));
    /* 更新摄像机 Y（上向量） 轴 = 摄像机右向量 x 摄像机方向向量 */
    m_camUp    = glm::normalize(glm::cross(m_camRight, m_camFront));
}

