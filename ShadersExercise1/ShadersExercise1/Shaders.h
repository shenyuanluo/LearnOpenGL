//
//  Shaders.h
//  Shaders
//
//  Created by shenyuanluo on 2017/9/6.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Shaders_h
#define Shaders_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


#define glCheckError() glCheckError_(__FILE__, __LINE__)


typedef enum {
    Shader_Vertex               = 0x00,             // 顶点着色器
    Shader_Fragment             = 0x01,             // 片段着色器
    Shader_Program              = 0x02,             // 着色器程序
}ShaderType;


/**
 检查 OpenGL 是否出错

 @param file 文件名
 @param line 行号
 @return 错误类型
 */
GLenum glCheckError_(const GLchar* file, GLint line);


class Shaders
{
private:
    
    // 着色器程序对象
    GLuint shaderProgramId;
    
    
    /**
     创建着色器对象

     @param shaderCode 着色器 GLSL 源码
     @param sType 着色器类型，参见‘ShaderType’
     @return 0，创建失败；> 0，成功创建的着色器对象引用 ID
     */
    GLuint createShader(const GLchar* shaderCode, ShaderType sType);
    
    
    /**
     创建着色器程序对象

     @param vShaderId 顶点着色器对象引用 ID
     @param fShaderId 片段着色器对象引用 ID
     @return 0，创建失败；> 0，成功创建的着色器程序对象引用 ID
     */
    GLuint createProgram(GLuint vShaderId, GLuint fShaderId);
    
    
    /**
     删除着色器

     @param shader 着色器对象引用 ID
     */
    void removeShader(GLuint shader);
    
    
    /**
     检查创建着色器是否出错

     @param shader 着色器对象引用 ID
     @param sType 着色器类型，参见‘ShaderType’
     */
    void checkShaderError(GLuint shader, ShaderType sType);
    
public:
    
    /**
     构造函数
     
     @param vsFilePath 顶点着色器 GLSL 源码文件路径
     @param fsFilePath 片段着色器 GLSL 源码文件路径
     */
    Shaders(const GLchar* vsFilePath, const GLchar* fsFilePath);
    
    
    /**
     析构函数
     */
    ~Shaders();
    
    
    /**
     激活着色器程序
     */
    void use();
};

#endif /* Shaders_h */

