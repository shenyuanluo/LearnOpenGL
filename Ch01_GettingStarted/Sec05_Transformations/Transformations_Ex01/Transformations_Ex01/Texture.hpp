//
//  Texture.hpp
//  Transformations_Ex01
//
//  Created by shenyuanluo on 2017/8/14.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <glad/glad.h>


class Texture
{
private:
    GLuint m_textureId;     /* 纹理对象 ID */
    
    
    /**
     创建纹理

     @param imgPath （纹理）图片路径
     @param internalFormat 纹理（内部存储）格式
     @param pixelFormat 图片（数据类型）格式
     @return 纹理对象引用 ID
     */
    GLuint createTexture(const GLchar* imgPath, GLint internalFormat, GLenum pixelFormat);
    
public:
    Texture(const GLchar* imgPath, GLint internalFormat, GLenum pixelFormat);
    
    ~Texture();
    
    /**
     设置纹理环绕方式

     @param sWrap S 轴环绕方式
     @param tWrap T 轴环绕方式
     */
    void setWrap(GLint sWrap, GLint tWrap);
    
    /**
     设置纹理过滤方式

     @param minFilter 缩小 过滤方式
     @param magFilter 放大 过滤方式
     */
    void setFilter(GLint minFilter, GLint magFilter);
    
    /**
     使用纹理
     */
    void use();
    
};

#endif /* Texture_hpp */
