//
//  Shaders.cpp
//  Shaders
//
//  Created by shenyuanluo on 2017/9/6.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Shaders.h"

#pragma mark - Public
#pragma mark -- 构造函数
Shaders::Shaders(const GLchar* vsFilePath, const GLchar* fsFilePath)
{
    std::string vertexString;
    std::string fragmentString;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    
    // 确保 ifstream 对象可以抛出异常
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // 打开文件
        vShaderFile.open(vsFilePath);
        fShaderFile.open(fsFilePath);
        
        std::stringstream vShaderStream;
        std::stringstream fShaderStream;
        
        // 读取文件流
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        // 关闭文件
        vShaderFile.close();
        fShaderFile.close();
        
        // 文件流转换成 string 字符串
        vertexString = vShaderStream.str();
        fragmentString = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::GLSL's file not successfuly read！" << std::endl;
    }
    const GLchar *vShaderCode;
    const GLchar *fShaderCode;
    
    // string 字符串 转换成 const GLchar *
    vShaderCode = vertexString.c_str();
    fShaderCode = fragmentString.c_str();
    
    GLuint vShaderId = createShader(vShaderCode, Shader_Vertex);
    GLuint fShaderId = createShader(fShaderCode, Shader_Fragment);
    shaderProgramId  = createProgram(vShaderId, fShaderId);
    
    removeShader(vShaderId);
    removeShader(fShaderId);
}


#pragma mark -- 析构函数
Shaders::~Shaders()
{
    glDeleteProgram(this->shaderProgramId);
}


#pragma mark -- 设置 uniform 的值
void Shaders::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->shaderProgramId, name.c_str()), (GLint)value);
}


void Shaders::setInt(const std::string &name, GLint value) const
{
    glUniform1i(glGetUniformLocation(this->shaderProgramId, name.c_str()), value);
}


void Shaders::setFloat(const std::string &name, GLfloat value) const
{
    glUniform1f(glGetUniformLocation(this->shaderProgramId, name.c_str()), value);
}

#pragma mark -- 激活着色器程序
void Shaders::use()
{
    glUseProgram(this->shaderProgramId);
}


GLuint Shaders::getShaderProgramId()
{
    return this->shaderProgramId;
}


#pragma mark - Private
#pragma mark -- 创建着色器对象
GLuint Shaders::createShader(const GLchar* shaderCode, ShaderType sType)
{
    if (NULL == shaderCode)
    {
        std::cout << "Can not create shader，shaderCode = " << shaderCode << std::endl;
        return 0;
    }
    GLuint shaderId;
    switch (sType)
    {
        case Shader_Vertex:         // 顶点着色器
        {
            shaderId = glCreateShader(GL_VERTEX_SHADER);
        }
            break;
            
        case Shader_Fragment:       // 片段着色器
        {
            shaderId = glCreateShader(GL_FRAGMENT_SHADER);
        }
            break;
            
        default:
            shaderId = 0;
            break;
    }
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);
    
    checkShaderError(shaderId, Shader_Vertex);
    
    return shaderId;
}


#pragma mark -- 创建着色器程序对象
GLuint Shaders::createProgram(GLuint vShaderId, GLuint fShaderId)
{
    if (0 == vShaderId || 0 == fShaderId)
    {
        std::cout << "Can not create shader program，vShaderid = " << vShaderId << ", fShaderId = " << fShaderId << std::endl;
        return 0;
    }
    GLuint shaderProgramId;
    shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vShaderId);
    glAttachShader(shaderProgramId, fShaderId);
    glLinkProgram(shaderProgramId);
    
    checkShaderError(shaderProgramId, Shader_Program);
    
    return shaderProgramId;
}


#pragma mark -- 删除着色器
void Shaders::removeShader(GLuint shader)
{
    if (0 == shader)
    {
        std::cout << "Can not remove shader，shader = " << shader << std::endl;
        return;
    }
    glDeleteShader(shader);
}


#pragma mark -- 检查创建着色器是否出错
void Shaders::checkShaderError(GLuint shader, ShaderType sType)
{
    if (0 == shader)
    {
        std::cout << "Can not check shader error，shader = " << shader << std::endl;
        return;
    }
    GLint success;
    GLchar infoLog[1024];
    switch (sType)
    {
        case Shader_Vertex:             // 顶点着色器
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "Create vertex shader failure！" << infoLog << std::endl;
            }
        }
            break;
            
        case Shader_Fragment:           // 片段着色器
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "Create fragment shader failure！" << infoLog << std::endl;
            }
        }
            break;
            
        case Shader_Program:            // 着色器程序
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "Create shader program failure!" << infoLog << std::endl;
            }
        }
            break;
            
        default:
            break;
    }
}


#pragma mark - Global
#pragma mark -- 检查 OpenGL 是否出错
GLenum glCheckError_(const GLchar *file, GLint line)
{
    GLenum errorCode;
    while (GL_NO_ERROR != (errorCode = glGetError()))
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                   // 枚举参数不合法
                error = "INVALID_ENUM";
                break;
                
            case GL_INVALID_VALUE:                  // 值参数不合法
                error = "INVALID_VALUE";
                break;
                
            case GL_INVALID_OPERATION:              // 一个指令的状态对指令的参数不合法
                error = "INVALID_OPERATION";
                break;
                
//            case GL_STACK_OVERFLOW:               // 压栈操作造成栈上溢(Overflow)  // OpenGL 4.0 以上版本才支持
//                error = "STACK_OVERFLOW";
//                break;
//
//            case GL_STACK_UNDERFLOW:              // 弹栈操作时栈在最低点（即栈下溢(Underflow)）  // OpenGL 4.0 以上版本才支持
//                error = "STACK_UNDERFLOW【】";
//                break;
                
            case GL_OUT_OF_MEMORY:                  // 内存调用操作无法调用（足够的）内存
                error = "OUT_OF_MEMORY";
                break;
                
            case GL_INVALID_FRAMEBUFFER_OPERATION:  // 读取或写入一个不完整的帧缓冲
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
