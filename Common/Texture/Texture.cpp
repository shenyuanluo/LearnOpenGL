//
//  Texture.cpp
//  
//
//  Created by shenyuanluo on 2017/8/13.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Texture.hpp"
#include <iostream>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#pragma mark - Public
#pragma mark -- 构造函数(2D 纹理)
Texture::Texture(const GLchar* imgPath)
{
    if (NULL == imgPath)
    {
        std::cout << "（纹理）图片路径不存在，无法创建纹理！" << std::endl;
        return;
    }
    m_2DTextureId = create2DTexture(imgPath);
    
    set2DWrap(GL_REPEAT, GL_REPEAT);
    set2DFilter(GL_LINEAR, GL_LINEAR);
}

#pragma mark -- 构造函数(2D 纹理)
Texture::Texture(const GLchar* imgPath, GLint internalFormat, GLenum pixelFormat)
{
    if (NULL == imgPath)
    {
        std::cout << "（纹理）图片路径不存在，无法创建纹理！" << std::endl;
        return;
    }
    m_2DTextureId = createTexture(imgPath, internalFormat, pixelFormat);
    
    set2DWrap(GL_REPEAT, GL_REPEAT);
    set2DFilter(GL_LINEAR, GL_LINEAR);
}

#pragma mark -- 构造函数(立方体纹理)
Texture::Texture(std::vector<std::string> cubImgPaths)
{
    m_3DTextureId = create3DTexture(cubImgPaths);
    
    set3DWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    set3DFilter(GL_LINEAR, GL_LINEAR);
}

#pragma mark -- 析构函数
Texture::~Texture()
{

}

#pragma mark -- 设置(2D)纹理环绕方式
void Texture::set2DWrap(GLint sWrap, GLint tWrap) const
{
    /* 设置之前先绑定纹理 */
    glBindTexture(GL_TEXTURE_2D, m_2DTextureId);
    /* 设置纹理环绕(S 轴)方式 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
    /* 设置纹理环绕(T 轴)方式 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
}

#pragma mark -- 设置(3D)纹理环绕方式
void Texture::set3DWrap(GLint sWrap, GLint tWrap, GLint rWrap) const
{
    /* 设置之前先绑定纹理 */
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_3DTextureId);
    /* 设置纹理环绕(S 轴)方式 */
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, sWrap);
    /* 设置纹理环绕(T 轴)方式 */
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, tWrap);
    /* 设置纹理环绕(R 轴)方式 */
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, rWrap);
}

#pragma mark -- 设置(2D)纹理过滤方式
void Texture::set2DFilter(GLint minFilter, GLint magFilter) const
{
    /* 设置之前先绑定纹理 */
    glBindTexture(GL_TEXTURE_2D, m_2DTextureId);
    /* 设置纹理过滤(缩小)方式 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    /* 设置纹理过滤(放大)方式 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

#pragma mark -- 设置(3D)纹理过滤方式
void Texture::set3DFilter(GLint minFilter, GLint magFilter) const
{
    /* 设置之前先绑定纹理 */
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_3DTextureId);
    /* 设置纹理过滤(缩小)方式 */
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilter);
    /* 设置纹理过滤(放大)方式 */
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, magFilter);
}

#pragma mark -- 使用(2D)纹理
GLuint Texture::texture2DId() const
{
    return m_2DTextureId;
}

#pragma mark -- 使用(3D)纹理
GLuint Texture::texture3DId() const
{
    return m_3DTextureId;
}

#pragma mark -- 激活并绑定(2D)纹理到指定的纹理单元
void Texture::use2D(GLenum unit) const
{
    glActiveTexture(unit);  // 先激活对应的纹理单元
    glBindTexture(GL_TEXTURE_2D, m_2DTextureId);    // 绑定纹理
}

#pragma mark -- 激活并绑定(3D)纹理到指定的纹理单元
void Texture::use3D(GLenum unit) const
{
    glActiveTexture(unit);  // 先激活对应的纹理单元
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_3DTextureId);  // 绑定纹理
}

#pragma mark -- 释放(2D)纹理
void Texture::free2DTexture()
{
    glDeleteTextures(1, &m_2DTextureId);
}

#pragma mark -- 释放(3D)纹理
void Texture::free3DTexture()
{
    glDeleteTextures(1, &m_3DTextureId);
}


#pragma mark - Private
#pragma mark -- 创建(2D)纹理
GLuint Texture::create2DTexture(const GLchar* imgPath) const
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
    GLint colorChn;    /* 纹理图片 颜色通道的个数 */
    /* 加载纹理图片 */
    GLubyte* imgData = stbi_load(imgPath, &imgWidth, &imgHeight, &colorChn, 0);
    /* 设置图片倒转 */
    stbi_set_flip_vertically_on_load(true);
    if (!imgData)
    {
        std::cout << "加载（纹理）图片失败！" << std::endl;
    }
    else
    {
        GLenum format = GL_RGB;
        if (1 == colorChn)
            format = GL_RED;
        else if (3 == colorChn)
            format = GL_RGB;
        else if (4 == colorChn)
            format = GL_RGBA;
        
        /* 生成纹理 */
        glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, imgData);
        /* 生成多级渐远纹理*/
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(imgData);   /* 纹理绑定成功后，释放图片内存 */
    
    return textureId;
}

#pragma mark -- 创建(2D)纹理
GLuint Texture::createTexture(const GLchar* imgPath, GLint internalFormat, GLenum pixelFormat) const
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
    GLint colorChn;    /* 纹理图片 颜色通道的个数 */
    /* 加载纹理图片 */
    GLubyte* imgData = stbi_load(imgPath, &imgWidth, &imgHeight, &colorChn, 0);
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

#pragma mark -- 创建(3D)纹理
GLuint Texture::create3DTexture(std::vector<std::string> cubImgPaths)
{
    if (0 >= cubImgPaths.size())
    {
        return 0;
    }
    /* 声明一个引用 纹理对象 ID */
    GLuint textureId;
    /* 创建 纹理对象 */
    glGenTextures(1, &textureId);
    /* 绑定 纹理对象，指明是 3D 纹理(立方体贴图) */
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    
    GLint imgWidth;     /* 纹理图片 宽度 */
    GLint imgHeight;    /* 纹理图片 高度 */
    GLint colorChn;     /* 纹理图片 颜色通道数 */
    /* 加载纹理图片 */
    for (GLint i = 0; i < cubImgPaths.size(); i++)
    {
        /* 禁止图片倒转
         （这里禁止倒转，我个人理解（暂时不知对错）是天空盒子是在内部看的，而立方体箱子是在外部看的，
         图片的坐标原点是左上角，而 OpenGL 纹理的坐标原点是左下角，刚好对图像进行了倒转；
         又因是从内部查看，所有不需再次转回来。）*/
        stbi_set_flip_vertically_on_load(false);
        GLubyte* imgData = stbi_load(cubImgPaths[i].c_str(), &imgWidth, &imgHeight, &colorChn, 0);
        if (!imgData)
        {
            std::cout << "加载 3D（纹理）图片：" << i << " 失败！" << std::endl;
            stbi_image_free(imgData);   /* 纹理绑定成功后，释放图片内存 */
            continue;
        }
        else
        {
            GLenum format = GL_RGB;
            if (1 == colorChn)
                format = GL_RED;
            else if (3 == colorChn)
                format = GL_RGB;
            else if (4 == colorChn)
                format = GL_RGBA;
            
            /* 生成(对应的面)纹理 */
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, imgData);
            stbi_image_free(imgData);   /* 纹理绑定成功后，释放图片内存 */
        }
    }
    
    return textureId;
}
