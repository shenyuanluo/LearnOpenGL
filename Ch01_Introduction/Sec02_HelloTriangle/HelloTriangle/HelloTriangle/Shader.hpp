//
//  Shader.hpp
//  HelloTriangle
//
//  Created by shenyuanluo on 2017/8/11.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


typedef enum {
    Shader_vertex               = 0x00,     /* 顶点着色器 */
    Shader_fragment             = 0x01,     /* 片段着色器 */
    Shader_program              = 0x02,     /* 着色器程序 */
}ShaderType;


class Shader
{
private:
    GLuint m_programId;     /* 着色器程序 ID */
    
    
    /**
     创建着色器

     @param shaderCode GLSL 源代码
     @param sType 着色器类型，参见‘ShaderType’
     @return 成功，则返回着色器引用 ID；失败，则返回 0
     */
    GLuint createShader(const GLchar* shaderCode, ShaderType sType);
    
    /**
     创建着色器程序
     
     @param vShaderId 顶点着色器引用 ID
     @param fShaderId 片段着色器引用 ID
     @return 成功，则返回着色器程序引用 ID；失败，则返回 0
     */
    GLuint createProgram(GLuint vShaderId, GLuint fShaderId);
    
    /**
     移除着色器
     
     @param shaderId 着色器引用 ID
     @param sType 着色器类型，参见‘ShaderType’
     */
    void removeShader(GLuint shaderId, ShaderType sType);
    
    /**
     检查着色器是否出错
     
     @param shaderId 着色器引用 ID
     @param sType 着色器类型，参见‘ShaderType’
     @return true：成功，false：失败
     */
    bool checkShaderError(GLuint shaderId, ShaderType sType);
    
public:
    
    Shader(const GLchar* vCodePath, const GLchar* fCodePath);
    
    ~Shader();
    
    /**
     使用着色器
     */
    void use();
    
};

#endif /* Shader_hpp */
