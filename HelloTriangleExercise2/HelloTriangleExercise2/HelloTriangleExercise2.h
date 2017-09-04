//
//  HelloTriangleExercise2.h
//  HelloTriangleExercise2
//
//  Created by shenyuanluo on 2017/9/4.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef HelloTriangleExercise2_h
#define HelloTriangleExercise2_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

typedef enum {
    RetError                = 0,        // 错误
    RetSuccess              = 1,        // 成功
}RetStatus;

/**
 初始化窗体
 
 @return 成功创建的窗体
 */
GLFWwindow * initWindow();

/**
 初始化 GLAD
 
 @return 是否初始化成功，参见‘RetStatus’
 */
RetStatus initGlad();

/**
 渲染顶点数据
 
 @param window 窗体
 @param vertexBuff1 顶点数据缓冲
 @param buffLen1 缓冲长度
 @param vertexBuff2 顶点数据缓冲
 @param buffLen2 缓冲长度
 */
void render(GLFWwindow *window, GLfloat *vertexBuff1, GLint buffLen1, GLfloat *vertexBuff2, GLint buffLen2);

#endif /* HelloTriangleExercise2_h */
