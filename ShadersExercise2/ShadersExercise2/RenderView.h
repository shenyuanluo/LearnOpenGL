//
//  RenderView.h
//  Shaders
//
//  Created by shenyuanluo on 2017/10/1.
//  Copyright © 2017年 shenyuanluo. All rights reserved.
//

#ifndef RenderView_h
#define RenderView_h

#include "Shaders.h"

typedef enum {
    RetError                = 0,        // 错误
    RetSuccess              = 1,        // 成功
}RetStatus;


class RenderView
{
private:
    
    // 窗体
    GLFWwindow* window;
    
    // 大小
    const GLuint SCR_Width;
    const GLuint SCR_Height;
    
    // 标题
    const GLchar* SCR_Title;
    
    /**
     GLFW window 大小改变回调
     
     @param window 窗体实例
     @param width 窗体宽度
     @param height 窗体高度
     */
    static void frameBuffSizeCB(GLFWwindow* window, GLint width, GLint height);
    
    
    /**
     处理用户输入
     
     @param window 窗体实例
     */
    void processInput(GLFWwindow* window);
    
    /**
     创建顶点数组对象
     
     @return 0，创建失败；> 0，成功创建的顶点数组对象 ID
     */
    GLuint createVAO();
    
    
    /**
     创建顶点缓冲对象
     
     @param vertexBuff 顶点数组缓冲
     @param buffLen 顶点数组长度
     @return 0，创建失败；> 0，成功创建的顶点缓冲对象 ID
     */
    GLuint createVBO(GLfloat* vertexBuff, GLuint buffLen);
    
    
    /**
     创建索引缓冲对象
     
     @param indicesBuff 索引数组缓冲
     @param buffLen 索引数组长度
     @return 0，创建失败；> 0，成功创建的索引缓冲对象 ID
     */
    GLuint createEBO(GLuint* indicesBuff, GLuint buffLen);
    
public:
    
    RenderView(const GLuint width, const GLuint height, const GLchar* title);
    ~RenderView();
    
    
    /**
     初始化 GLAD
     
     @return 是否初始化成功，参见‘RetStatus’
     */
    RetStatus initGlad();
    
    
    /**
     渲染顶点数据
     
     @param vertexBuff 顶点数据缓冲
     @param buffLen 缓冲长度
     */
    void render(GLfloat* vertexBuff, GLuint buffLen);
    
};

#endif /* RenderView_h */
