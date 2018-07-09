//
//  Camera.cpp
//  
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

#pragma mark -- 析构函数
Camera::~Camera()
{
    
}

#pragma mark -- 使用摄像机（观察矩阵）
GLfloat* Camera::use()
{
	/* 使用自 glm 内置函数创建 */
    m_viewMat = glm::lookAt(m_camPos, m_camPos + m_camFront, m_camUp);
	/* 使用自定义函数创建 */
//    m_viewMat = createLookAt(m_camPos, m_camPos + m_camFront, m_camUp);
    return glm::value_ptr(m_viewMat);
}

#pragma mark -- 获取视野
GLfloat Camera::fov() const
{
    return glm::radians(m_zoom);
}

#pragma mark -- 获取观察矩阵
glm::mat4 Camera::viewMatrix()
{
    m_viewMat = glm::lookAt(m_camPos, m_camPos + m_camFront, m_camUp);
    return m_viewMat;
}

#pragma mark -- 获取摄像机'位置'向量
glm::vec3 Camera::position() const
{
    return m_camPos;
}

#pragma mark -- 获取摄像机'方向'向量
glm::vec3 Camera::front() const
{
    return m_camFront;
}

#pragma mark -- 获取摄像机‘上’向量
glm::vec3 Camera::up() const
{
    return m_camUp;
}

#pragma mark --获取摄像机‘右’向量
glm::vec3 Camera::right() const
{
    return m_camRight;
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
            
        case Move_up:       /* 向上移动 */
            m_camPos += m_camUp * velocity;
            break;
            
        case Move_down:     /* 向下移动 */
            m_camPos -= m_camUp * velocity;
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
glm::mat4 Camera::createLookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
    /*
               _               _     _              _
              |  Rx  Ry  Rz  0  |   |  1  0  0  -Px  |
     lookAt = |  Ux  Uy  Uz  0  | * |  0  1  0  -Py  |
              |  Dx  Dy  Dz  0  |   |  0  0  1  -Pz  |
              |_ 0   0   0   1 _|   |_ 0  0  0   1  _|
     
     其中 R 是右向量，U 是上向量，D 是方向向量， P是摄像机位置向量。
     注意，位置向量是相反的，因为最终把世界平移到与我们自身移动的相反方向
     */
    
    /* 计算摄像机 Z（方向向量） 轴 */
    glm::vec3 zAxis = glm::normalize(position - target);
    /* 计算摄像机 X 轴（右向量） */
    glm::vec3 xAxis = glm::normalize(glm::cross(glm::normalize(worldUp), zAxis));
    // 4. Calculate camera up vector
    /* 计算摄像机 Y 轴（上向量） */
    glm::vec3 yAxis = glm::cross(zAxis, xAxis);
    
    /* 创建平移矩阵 */
    glm::mat4 translation; /* 创建单位矩阵 */
    translation[3][0] = -position.x;    /* 设置位置向量‘x’ 坐标量 */
    translation[3][1] = -position.y;    /* 设置位置向量‘y’ 坐标量 */
    translation[3][2] = -position.z;    /* 设置位置向量‘z’ 坐标量 */
    
    /* 创建旋转矩阵 */
    glm::mat4 rotation;
    rotation[0][0] = xAxis.x;       /* 设置 X 轴 ‘x’ 坐标量 */
    rotation[1][0] = xAxis.y;       /* 设置 X 轴 ‘y’ 坐标量 */
    rotation[2][0] = xAxis.z;       /* 设置 X 轴 ‘z’ 坐标量 */
    rotation[0][1] = yAxis.x;       /* 设置 Y 轴 ‘x’ 坐标量 */
    rotation[1][1] = yAxis.y;       /* 设置 Y 轴 ‘y’ 坐标量 */
    rotation[2][1] = yAxis.z;       /* 设置 Y 轴 ‘z’ 坐标量 */
    rotation[0][2] = zAxis.x;       /* 设置 Z 轴 ‘x’ 坐标量 */
    rotation[1][2] = zAxis.y;       /* 设置 Z 轴 ‘y’ 坐标量 */
    rotation[2][2] = zAxis.z;       /* 设置 Z 轴 ‘z’ 坐标量 */
    
    /* 创建 Look At（观察）矩阵 */
    return rotation * translation;
}
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

