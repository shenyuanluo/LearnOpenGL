//
//  Shader.hpp
//  Transformations_Ex01
//
//  Created by shenyuanluo on 2017/8/14.
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
     获取 Uniform 变量地址

     @param name uniform 变量-key
     @return uniform 变量地址
     */
    GLint uniformLocation(const std::string &name) const;
    
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
     设置 uniform(bool 类型) 的值

     @param name uniform 变量-key
     @param value uniform 变量-value
     */
    void setUniformBool(const std::string &name, bool value);
    
    /**
     设置 uniform(int 类型) 的值

     @param name uniform 变量-key
     @param v1 uniform 变量-value
     */
    void setUniformInt1(const std::string &name, GLint v1);
    
    void setUniformInt2(const std::string &name, GLint v1, GLint v2);
    
    void setUniformInt3(const std::string &name, GLint v1, GLint v2, GLint v3);
    
    void setUniformInt4(const std::string &name, GLint v1, GLint v2, GLint v3, GLint v4);
    
    /**
     设置 uniform(float 类型) 的值

     @param name uniform 变量-key
     @param v1 uniform 变量-value
     */
    void setUniformFloat1(const std::string &name, GLfloat v1);
    
    void setUniformFloat2(const std::string &name, GLfloat v1, GLfloat v2);
    
    void setUniformFloat3(const std::string &name, GLfloat v1, GLfloat v2, GLfloat v3);
    
    void setUniformFloat4(const std::string &name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4);
    
    /**
     设置 uniform(Matrix 类型) 的值
     
     @param name uniform 变量-key
     @param value uniform 变量-value
     */
    void setUniformMat4(const std::string &name, const GLfloat* value);
    
    /**
     使用着色器
     */
    void use();
    
};

#endif /* Shader_hpp */
