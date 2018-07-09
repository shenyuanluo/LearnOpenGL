//
//  Window.hpp
//  HelloTriangle_Ex03
//
//  Created by shenyuanluo on 2017/8/11.
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
    std::string     m_cwd;              /** 可执行文件路径 */

    
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
     获取文件的绝对路径
     
     @param filePath 文件相对路径
     @return 绝对路径
     */
    std::string fullPath(const std::string &filePath);
    
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
     设置顶点数组对象
     
     @param outVBO 顶点缓存对象引用 ID
     @param vertexBuff 顶点缓存
     @param vbLen 顶点缓存长度
     @param outEBO 索引缓存对象引用 ID
     @param indicesBuff 索引缓存
     @param ibLen 索引缓存长度
     @return 成功，则返回顶点数组对象引用 ID；失败，则返回 0
     */
    GLuint configVAO(GLuint* outVBO, GLfloat* vertexBuff, GLuint vbLen, GLuint* outEBO, GLuint* indicesBuff, GLuint ibLen);    
    
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
     设置可执行文件所在目录·绝对路径
     
     @param cwdPath 可执行文件绝对路径
     */
    void setCWD(const std::string &cwdPath);
    
    /**
     渲染
     
     @param vertexBuff1 顶点缓冲
     @param buffLen1 缓冲长度
     @param vertexBuff2 顶点缓冲
     @param buffLen2 缓冲长度
     */
    void render(GLfloat* vertexBuff1, GLuint buffLen1, GLfloat* vertexBuff2, GLuint buffLen2);
};

#endif /* Window_hpp */
