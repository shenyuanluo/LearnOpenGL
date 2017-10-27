//
//  RenderView.h
//  Shaders
//
//  Created by shenyuanluo on 2017/10/1.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
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
    
    
    /**
     创建纹理对象

     @param internalformat 纹理颜色组成数量：GL_RGB ...
     @param pixelFormat 纹理像素数据格式：GL_RGB、GL_RBGA
     @param imgName 纹理图片名
     @return 0，创建失败；> 0，成功创建的纹理引用对象 ID
     */
    GLuint createTexture(GLint internalformat, GLenum pixelFormat, const GLchar* imgName);
    
public:
    
    RenderView(const GLuint width, const GLuint height, const GLchar* title);
    ~RenderView();
    
    
    /**
     获取窗体‘宽度’

     @return 窗体‘宽度’
     */
    const GLuint getSCRWidth();
    
    
    /**
     获取窗体‘高度’
     
     @return 窗体‘高度’
     */
    const GLuint getSCRHeight();
    
    
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
