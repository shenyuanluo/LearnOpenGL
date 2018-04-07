//
//  Shader.cpp
//  Camera
//
//  Created by shenyuanluo on 2017/8/16.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Shader.hpp"


#define LOG_BUF_LEN 512     /* log 输出缓冲区长度 */

#pragma mark - Public
#pragma mark -- 构造函数
Shader::Shader(const GLchar* vCodePath, const GLchar* fCodePath)
{
    std::string vString;
    std::string fString;
    std::ifstream vsFile;
    std::ifstream fsFile;
    /* 确保 ifstream 对象可以抛出异常 */
    vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    /* 读取 GLSL */
    try
    {
        /* 打开文件 */
        vsFile.open(vCodePath);
        fsFile.open(fCodePath);
        
        std::stringstream vsStream;
        std::stringstream fsStream;
        
        /* 读取文件流 */
        vsStream << vsFile.rdbuf();
        fsStream << fsFile.rdbuf();
        
        /* 关闭文件 */
        vsFile.close();
        fsFile.close();
        
        /* 文件流转换成 String 字符串 */
        vString = vsStream.str();
        fString = fsStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "读取 GLSL 文件失败！" << std::endl;
    }
    
    /* String 字符串转换成 const GLchar* */
    const GLchar* vsCode = vString.c_str();
    const GLchar* fsCode = fString.c_str();
    
    GLuint vShaderId = createShader(vsCode, Shader_vertex);
    GLuint fShaderId = createShader(fsCode, Shader_fragment);
    
    m_programId = createProgram(vShaderId, fShaderId);
    
    /* 已成功链接到 Program 的 shader 可以移除 */
    removeShader(vShaderId, Shader_vertex);
    removeShader(fShaderId, Shader_fragment);
}

#pragma mark -- 析构函数
Shader::~Shader()
{
    removeShader(m_programId, Shader_program);
}

#pragma mark -- 设置 uniform(bool 类型) 的值
void Shader::setUniformBool(const std::string &name, bool value)
{
    setUniformInt1(name, (GLint)value);
}

#pragma mark -- 设置 uniform(int 类型) 的值
void Shader::setUniformInt1(const std::string &name, GLint v1)
{
    use();
    glUniform1i(uniformLocation(name), v1);
}

void Shader::setUniformInt2(const std::string &name, GLint v1, GLint v2)
{
    use();
    glUniform2i(uniformLocation(name), v1, v2);
}

void Shader::setUniformInt3(const std::string &name, GLint v1, GLint v2, GLint v3)
{
    use();
    glUniform3i(uniformLocation(name), v1, v2, v3);
}

void Shader::setUniformInt4(const std::string &name, GLint v1, GLint v2, GLint v3, GLint v4)
{
    use();
    glUniform4i(uniformLocation(name), v1, v2, v3, v4);
}

#pragma mark -- 设置 uniform(float 类型) 的值
void Shader::setUniformFloat1(const std::string &name, GLfloat v1)
{
    use();
    glUniform1f(uniformLocation(name), v1);
}

void Shader::setUniformFloat2(const std::string &name, GLfloat v1, GLfloat v2)
{
    use();
    glUniform2f(uniformLocation(name), v1, v2);
}

void Shader::setUniformFloat3(const std::string &name, GLfloat v1, GLfloat v2, GLfloat v3)
{
    use();
    glUniform3f(uniformLocation(name), v1, v2, v3);
}

void Shader::setUniformFloat4(const std::string &name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4)
{
    use();
    glUniform4f(uniformLocation(name), v1, v2, v3, v4);
}

void Shader::setUniformMat4(const std::string &name, const GLfloat* value)
{
    use();
    glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, value);
}

#pragma mark -- 激活着色器程序
void Shader::use()
{
    glUseProgram(m_programId);
}


#pragma mark - Private
#pragma mark -- 创建着色器
GLuint Shader::createShader(const GLchar* shaderCode, ShaderType sType)
{
    if (NULL == shaderCode)
    {
        std::cout << "无法创建着色器！" << std::endl;
        return 0;
    }
    /* 声明一个着色器对象引用 ID */
    GLuint shaderId;
    switch (sType)
    {
        case Shader_vertex:
            /* 创建 着色器（指明是顶点着色器） */
            shaderId = glCreateShader(GL_VERTEX_SHADER);
            break;
            
        case Shader_fragment:
            /* 创建 着色器（指明是片段着色器） */
            shaderId = glCreateShader(GL_FRAGMENT_SHADER);
            break;
            
        default:
            shaderId = 0;
            break;
    }
    /* 执行创建着色器 GLSL 的源码 */
    glShaderSource(shaderId, 1, &shaderCode, NULL);
    /* 编译 GLSL 源码 */
    glCompileShader(shaderId);
    /* 检查 着色器是否编译出错 */
    checkShaderError(shaderId, sType);
    
    return shaderId;
}

#pragma mark -- 创建着色器程序
GLuint Shader::createProgram(GLuint vShaderId, GLuint fShaderId)
{
    if (0 == vShaderId || 0 == fShaderId)
    {
        std::cout << "无法创建着色器程序！" << std::endl;
        return 0;
    }
    /* 声明一个着色器程序对象引用 ID */
    GLuint programId;
    /* 创建着色器程序 */
    programId = glCreateProgram();
    /* 添加 顶点着色器 */
    glAttachShader(programId, vShaderId);
    /* 添加 片段着色器 */
    glAttachShader(programId, fShaderId);
    /* 链接 着色器程序 */
    glLinkProgram(programId);
    /* 检查 着色器程序是否链接出错 */
    checkShaderError(programId, Shader_program);
    
    return programId;
}

#pragma mark -- 获取 Uniform 变量 地址
GLint Shader::uniformLocation(const std::string &name) const
{
    if (name.empty() || 0 == m_programId)
    {
        return -1;
    }
    GLint location = glGetUniformLocation(m_programId, name.c_str());
    return location;
}

#pragma mark -- 移除着色器
void Shader::removeShader(GLuint shaderId, ShaderType sType)
{
    switch (sType)
    {
        case Shader_vertex:
            /* 释放着色器对象 */
            glDeleteShader(shaderId);
            break;
            
        case Shader_fragment:
            /* 释放着色器对象 */
            glDeleteShader(shaderId);
            break;
            
        case Shader_program:
            /* 释放着色器程序对象 */
            glDeleteProgram(shaderId);
            break;
            
        default:
            break;
    }
}

#pragma mark -- 检查着色器是否出错
bool Shader::checkShaderError(GLuint shaderId, ShaderType sType)
{
    GLint isSuccess;
    GLchar infoLog[LOG_BUF_LEN];
    switch (sType)
    {
        case Shader_vertex:
        {
            /* 检查编译 GLSL 是否出错 */
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isSuccess);
            /* 编译失败 */
            if (!isSuccess)
            {
                /* 获取编译信息 */
                glGetShaderInfoLog(shaderId, LOG_BUF_LEN, NULL, infoLog);
                std::cout << "编译顶点着色器失败：\n" << infoLog << std::endl;
            }
        }
            break;
            
        case Shader_fragment:
        {
            /* 检查编译 GLSL 是否出错 */
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isSuccess);
            /* 编译失败 */
            if (!isSuccess)
            {
                /* 获取编译信息 */
                glGetShaderInfoLog(shaderId, LOG_BUF_LEN, NULL, infoLog);
                std::cout << "编译片段着色器失败：\n" << infoLog << std::endl;
            }
        }
            break;
            
        case Shader_program:
        {
            /* 检查着色器程序链接是否出错 */
            glGetProgramiv(shaderId, GL_LINK_STATUS, &isSuccess);
            /* 链接失败 */
            if (!isSuccess)
            {
                glGetProgramInfoLog(shaderId, LOG_BUF_LEN, NULL, infoLog);
                /* 获取链接信息 */
                std::cout << "链接着色器程序失败：\n" << infoLog << std::endl;
            }
        }
            break;
            
        default:
            break;
    }
    return isSuccess;
}
