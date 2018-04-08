//
//  Texture.cpp
//  Textures
//
//  Created by shenyuanluo on 2017/8/13.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Texture.hpp"
#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#pragma mark - Public
#pragma mark -- 构造函数
Texture::Texture(const GLchar* imgPath, GLint internalFormat, GLenum pixelFormat)
{
    if (NULL == imgPath)
    {
        std::cout << "（纹理）图片路径不存在，无法创建纹理！" << std::endl;
        return;
    }
    m_textureId = createTexture(imgPath, internalFormat, pixelFormat);
    
    setWrap(GL_REPEAT, GL_REPEAT);
    setFilter(GL_LINEAR, GL_LINEAR);
}

#pragma mark -- 析构函数
Texture::~Texture()
{
    glDeleteTextures(1, &m_textureId);
}

#pragma mark -- 设置纹理环绕方式
void Texture::setWrap(GLint sWrap, GLint tWrap)
{
    /* 设置之前先绑定纹理 */
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    /* 设置纹理环绕(S 轴)方式 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
    /* 设置纹理环绕(T 轴)方式 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
}

#pragma mark -- 设置纹理过滤方式
void Texture::setFilter(GLint minFilter, GLint magFilter)
{
    /* 设置之前先绑定纹理 */
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    /* 设置纹理过滤(缩小)方式 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    /* 设置纹理过滤(放大)方式 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

#pragma mark -- 使用纹理
void Texture::use()
{
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}

#pragma mark - Private
#pragma mark -- 创建纹理
GLuint Texture::createTexture(const GLchar* imgPath, GLint internalFormat, GLenum pixelFormat)
{
    if (NULL == imgPath)
    {
        return 0;
    }
    /* 声明一个引用 纹理对象 ID */
    GLuint textureId;
    /* 创建 纹理对象 */
    glGenTextures(1, &textureId);
    /* 绑定 纹理对象，指明是 2D 纹理 */
    glBindTexture(GL_TEXTURE_2D, textureId);
    

    GLint imgWidth;     /* 纹理图片 宽度 */
    GLint imgHeight;    /* 纹理图片 高度 */
    GLint nrChannel;    /* 纹理图片 颜色通道的个数 */
    /* 加载纹理图片 */
    GLubyte* imgData = stbi_load(imgPath, &imgWidth, &imgHeight, &nrChannel, 0);
    /* 设置图片倒转 */
    stbi_set_flip_vertically_on_load(true);
    if (!imgData)
    {
        std::cout << "加载（纹理）图片失败！" << std::endl;
    }
    else
    {
        /* 生成纹理 */
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, imgWidth, imgHeight, 0, pixelFormat, GL_UNSIGNED_BYTE, imgData);
        /* 生成多级渐远纹理*/
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(imgData);   /* 纹理绑定成功后，释放图片内存 */
    
    return textureId;
}
