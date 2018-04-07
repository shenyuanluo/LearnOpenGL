//
//  Window.hpp
//  Camera
//
//  Created by shenyuanluo on 2017/8/16.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <iostream>
#include <glad/glad.h>
#include <GLFW//glfw3.h>


typedef enum __retStatus {
    Ret_failure             = 0,        /* 失败 */
    Ret_success             = 1,        /* 成功 */
}RetStatus;


class Window
{
private:
    
    GLFWwindow*     m_window;           /** 窗体实例 */
    const GLuint    m_width;            /** 窗体宽度 */
    const GLuint    m_height;           /** 窗体高度 */
    const GLchar*   m_title;            /** 窗体标题 */

    GLfloat m_currFTime;                /* 当前帧时间 */
    GLfloat m_lastFTime;                /* 上一帧时间 */
    GLfloat m_dealFTime;                /* 每一帧处理时间 */
    
    
    /**
     创建 GLFW 窗体实例

     @return GLFW 实例
     */
    GLFWwindow* createWindow();
    
    /**
     初始化 GLAD
     
     @return 参见‘RetStatus’
     */
    RetStatus initGlad();
    
    /**
     处理用户输入回调
     
     @param window GLFW 窗体实例
     */
    void processInput(GLFWwindow* window);
    
    /**
     清理资源
     */
    void clearWindow();
    
    /**
     创建顶点数组对象
     
     @return 成功，则返回顶点数组对象引用 ID；失败，则返回 0
     */
    GLuint createVAO();
    
    /**
     创建顶点缓冲对象
     
     @param vertexBuff 顶点数组缓冲
     @param buffLen 顶点数组长度
     @return 成功，则返回顶点缓冲对象引用 ID；失败，则返回 0
     */
    GLuint createVBO(GLfloat* vertexBuff, GLuint buffLen);
    
    /**
     创建索引缓冲对象
     
     @param indicesBuff 索引数组缓冲
     @param buffLen 索引数组长度
     @return 成功，则返回索引缓冲对象 ID；失败，则返回 0
     */
    GLuint createEBO(GLuint* indicesBuff, GLuint buffLen);
    
    
    /**
     GLFW 错误回调
     
     @param errorCode 错误代码
     @param description 错误描述
     */
    static void errorCallback(GLint errorCode, const GLchar* description);
    
    /**
     GLFW 窗体大小回调
     
     @param window GLFW 窗体实例
     @param width 窗体款第
     @param height 窗体高度
     */
    static void frameBufferSizeCB(GLFWwindow* window, GLint width, GLint height);
    
    /**
     鼠标（移动）事件回调

     @param window GLFW 窗体实例
     @param posX 鼠标当前位置 x 坐标
     @param posY 鼠标当前位置 y 坐标
     */
    static void mouseMoveCB(GLFWwindow* window, GLdouble posX, GLdouble posY);
    
    /**
     鼠标（滚动）事件回调

     @param window GLFW 窗体实例
     @param offsetX 鼠标滚动 x 偏移量
     @param offsetY 鼠标滚动 y 偏移量
     */
    static void mouseScrollCB(GLFWwindow* window, GLdouble offsetX, GLdouble offsetY);
    
    
public:
    Window(GLuint width, GLuint height, const GLchar* title);
    
    ~Window();
    
    /**
     渲染
     
     @param vertexBuff 顶点缓冲
     @param buffLen 缓冲长度
     */
    void render(GLfloat* vertexBuff, GLuint buffLen);
};

#endif /* Window_hpp */
