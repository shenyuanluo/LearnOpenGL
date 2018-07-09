//
//  GLErrorCheck.cpp
//  
//
//  Created by shenyuanluo on 2017/8/11.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "GLErrorCheck.hpp"
#include <iostream>


#pragma mark -- 检查 OpenGL 是否出错
GLenum glCheckError_(const GLchar *file, GLint line)
{
    GLenum errorCode;
    while (GL_NO_ERROR != (errorCode = glGetError()))
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                   /* 枚举参数不合法 */
                error = "INVALID_ENUM";
                break;
                
            case GL_INVALID_VALUE:                  /* 值参数不合法 */
                error = "INVALID_VALUE";
                break;
                
            case GL_INVALID_OPERATION:              /* 一个指令的状态对指令的参数不合法 */
                error = "INVALID_OPERATION";
                break;
                
//            case GL_STACK_OVERFLOW:               /* 压栈操作造成栈上溢(Overflow)  // OpenGL 4.0 以上版本才支持 */
//                error = "STACK_OVERFLOW";
//                break;
//
//            case GL_STACK_UNDERFLOW:              /* 弹栈操作时栈在最低点（即栈下溢(Underflow)）  // OpenGL 4.0 以上版本才支持 */
//                error = "STACK_UNDERFLOW";
//                break;
                
            case GL_OUT_OF_MEMORY:                  /* 内存调用操作无法调用（足够的）内存 */
                error = "OUT_OF_MEMORY";
                break;
                
            case GL_INVALID_FRAMEBUFFER_OPERATION:  /* 读取或写入一个不完整的帧缓冲 */
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
