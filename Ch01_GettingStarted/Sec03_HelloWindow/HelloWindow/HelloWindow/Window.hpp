//
//  Window.hpp
//  HelloWindow
//
//  Created by shenyuanluo on 2017/8/10.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <iostream>
#include <glad/glad.h>
#include <GLFW//glfw3.h>


typedef enum __retStatus {
    Ret_failure             = 0,        // 失败
    Ret_success             = 1,        // 成功
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
    Window(GLuint width, GLuint height, GLchar* title);
    
    ~Window();
    
    /**
     渲染
     */
    void render();
};

#endif /* Window_hpp */
