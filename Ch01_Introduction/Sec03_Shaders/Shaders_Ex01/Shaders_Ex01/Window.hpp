//
//  Window.hpp
//  Shaders_Ex01
//
//  Created by shenyuanluo on 2017/8/12.
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
