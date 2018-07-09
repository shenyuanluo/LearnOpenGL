//
//  Camera.hpp
//  
//
//  Created by shenyuanluo on 2017/8/16.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>


/* 摄像机移动方向枚举 */
typedef enum __moveDirection {
    Move_forward            = 0,        /* 向’前‘移动 */
    Move_backward           = 1,        /* 向’后‘移动 */
    Move_left               = 2,        /* 向‘左’移动 */
    Move_right              = 3,        /* 向‘右’移动 */
    Move_up                 = 4,        /* 向‘上’移动 */
    Move_down               = 5,        /* 向‘下’移动 */
}MoveDirection;


/* 摄像机默认值 */
const GLfloat kYaw          = -90.0f;   /* 偏航角 */
const GLfloat kPitch        = 0.0f;     /* 俯仰角 */
const GLfloat kMoveSpeed    = 2.5f;     /* 移动速度 */
const GLfloat kSensitivity  = 0.1;      /* 敏感度 */
const GLfloat kZoom         = 45.0f;    /* 放大 */


class Camera
{
private:
    /* 摄像机属性 */
    glm::mat4 m_viewMat;            /* 观察矩阵 */
    glm::vec3 m_camPos;             /* 摄像机位置向量 */
    glm::vec3 m_camFront;           /* 摄像机方向向量 */
    glm::vec3 m_camUp;              /* 摄像机‘上’向量 */
    glm::vec3 m_camRight;           /* 摄像机‘右’向量 */
    glm::vec3 m_wordUp;             /* 世界空间‘上’向量 */

    /* 欧拉角 */
    GLfloat m_yaw;                  /* 偏航角 */
    GLfloat m_pitch;                /* 俯仰角角 */

    /* 摄像机选项 */
    GLfloat m_moveSpeed;            /* 移动速度 */
    GLfloat m_mouseSensitivity;     /* 鼠标敏感度 */
    GLfloat m_zoom;                 /* 放大 */

    glm::mat4 createLookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
    
    /**
     更新摄像机有关向量
     */
    void updateCameraVectors();

public:

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = kYaw, GLfloat pitch = kPitch);

    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat worldUpX, GLfloat worldUpY, GLfloat worldUpZ, GLfloat yaw, GLfloat pitch);
    
    ~Camera();

    /**
     使用摄像机（观察矩阵）

     @return 观察矩阵
     */
    GLfloat* use();

    /**
     获取（观察矩阵）视野（Field of View）

     @return 视野角度（弧度制）
     */
    GLfloat fov() const;
    
    /**
     获取观察矩阵
     
     @return 观察矩阵
     */
    glm::mat4 viewMatrix();
    
    /**
     获取摄像机'位置'向量

     @return 位置向量
     */
    glm::vec3 position() const;
    
    /**
     获取摄像机'方向'向量
     
     @return 方向向量
     */
    glm::vec3 front() const;
    
    /**
     获取摄像机‘上’向量

     @return 上向量
     */
    glm::vec3 up() const;
    
    /**
     获取摄像机‘右’向量

     @return 右向量
     */
    glm::vec3 right() const;

    /**
     键盘移动

     @param direction 移动方向，参见‘MoveDirection’
     @param dealTime 窗体渲染每帧时间（间隔）
     */
    void keyboardMove(MoveDirection direction, GLfloat dealTime);

    /**
     鼠标移动

     @param offsetX 鼠标位置 x 坐标偏移量
     @param offsetY 鼠标位置 y 坐标偏移量
     @param constrainPitch 偏航角度
     */
    void mouseMove(GLfloat offsetX, GLfloat offsetY, GLboolean constrainPitch = GL_TRUE);

    /**
     鼠标滚动

     @param offsetY 滚动偏移量
     */
    void mouseScroll(GLfloat offsetY);

};

#endif /* Camera_hpp */

