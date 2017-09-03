//
//  HelloTriangleExercise3.h
//  HelloTriangle
//
//  Created by shenyuanluo on 2017/9/1.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef HelloTriangle_h
#define HelloTriangle_h

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

 @param window 窗体实例
 @param vertexBuffYellow 顶点数据缓冲1
 @param buffLenYellow 缓冲1长度
 @param vertexBuffOrange 顶点数据缓冲2
 @param buffLenOrange 缓冲2长度
 */
void render(GLFWwindow *window, GLfloat *vertexBuffYellow, GLint buffLenYellow, GLfloat *vertexBuffOrange, GLint buffLenOrange);

#endif /* HelloTriangle_h */
