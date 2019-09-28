//
//  Shader.hpp
//  
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
#include <glm/glm.hpp>


typedef enum {
    Shader_vertex               = 0x00,     /* 顶点着色器 */
    Shader_geometry             = 0x01,     /* 几何着色器 */
    Shader_fragment             = 0x02,     /* 片段着色器 */
    Shader_program              = 0x03,     /* 着色器程序 */
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
    GLuint createShader(const GLchar* shaderCode, ShaderType sType) const;
    
    /**
     创建着色器程序
     
     @param vShaderId 顶点着色器引用 ID
     @param fShaderId 片段着色器引用 ID
     @return 成功，则返回着色器程序引用 ID；失败，则返回 0
     */
    GLuint createProgram(GLuint vShaderId, GLuint fShaderId) const;
    
    /**
     创建着色器程序

     @param vShaderId 顶点着色器引用 ID
     @param gShaderId 几何着色器引用 ID
     @param fShaderId 片段着色器引用 ID
     @return 成功，则返回着色器程序引用 ID；失败，则返回 0
     */
    GLuint createProgram(GLuint vShaderId, GLuint gShaderId, GLuint fShaderId) const;

    /**
     获取 Uniform 变量地址

     @param name uniform 变量-key
     @return uniform 变量地址
     */
    GLint uniformLocation(const std::string &name) const;
    
    /**
     获取 uniform-block 变量索引

     @param name uniform-block 变量-key
     @return uniform-block 索引
     */
    GLuint uniformBlockIndex(const std::string &name) const;

    /**
     移除着色器
     
     @param shaderId 着色器引用 ID
     @param sType 着色器类型，参见‘ShaderType’
     */
    void removeShader(GLuint shaderId, ShaderType sType) const;
    
    /**
     检查着色器是否出错
     
     @param shaderId 着色器引用 ID
     @param sType 着色器类型，参见‘ShaderType’
     @return true：成功，false：失败
     */
    bool checkShaderError(GLuint shaderId, ShaderType sType) const;
    
public:
    
    Shader(const GLchar* vCodePath, const GLchar* fCodePath);
    
    Shader(const GLchar* vCodePath, const GLchar* gCodePath, const GLchar* fCodePath);

    ~Shader();
    
    /**
     设置 uniform(bool 类型) 的值

     @param name uniform 变量-key
     @param value uniform 变量-value
     */
    void setUniformBool(const std::string &name, bool value) const;
    
    /**
     设置 uniform(int 类型) 的值
     
     @param name uniform 变量-key
     @param v1 uniform 变量-value
     */
    void setUniformInt(const std::string &name, GLint v1) const;
    
    /**
     设置 uniform(float 类型) 的值
     
     @param name uniform 变量-key
     @param v1 uniform 变量-value
     */
    void setUniformFloat(const std::string &name, GLfloat v1) const;

    /**
     设置 uniform(Vector 类型) 的值
     
     @param name uniform 变量-key
     @param value uniform 变量-value
     */
    void setUniformVec2(const std::string &name, const glm::vec2 &value) const;

    void setUniformVec2(const std::string &name, GLfloat x, GLfloat y) const;

    void setUniformVec3(const std::string &name, const glm::vec3 &value) const;
    
    void setUniformVec3(const std::string &name, GLfloat x, GLfloat y, GLfloat z) const;
    
    void setUniformVec4(const std::string &name, const glm::vec4 &value) const;

    void setUniformVec4(const std::string &name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;

    /**
     设置 uniform(Matrix 类型) 的值

     @param name uniform 变量-key
     @param mat uniform 变量-value
     */
    void setUniformMat2(const std::string &name, const glm::mat2 &mat) const;
    
    void setUniformMat2(const std::string &name, const GLfloat* value) const;
    
    void setUniformMat3(const std::string &name, const glm::mat3 &mat) const;
    
    void setUniformMat3(const std::string &name, const GLfloat* value) const;
    
    void setUniformMat4(const std::string &name, const glm::mat4 &mat) const;
    
    void setUniformMat4(const std::string &name, const GLfloat* value) const;
    
    /**
     绑定 Uniform-Block 到指定的绑定点

     @param name uniform-block 变量-key
     @param bindingPoint 绑定点：0, 1, 2, 3, ··· , n
     */
    void setUniformBlockToPoint(const std::string &name, GLuint bindingPoint);
    
    
    /**
     获取着色器程序对象 ID

     @return 着色器程序对象 ID
     */
    GLuint programId();

    /**
     使用着色器
     */
    void use() const;

};

#endif /* Shader_hpp */
