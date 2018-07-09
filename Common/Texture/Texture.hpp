//
//  Texture.hpp
//  
//
//  Created by shenyuanluo on 2017/8/13.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <glad/glad.h>
#include <vector>


class Texture
{
private:
    GLuint m_2DTextureId;       /* (2D)纹理对象 ID */
    GLuint m_3DTextureId;       /* (3D)纹理对象 ID */
    
    /**
     创建(2D)纹理
     
     @param imgPath （纹理）图片路径
     @return 纹理对象引用 ID
     */
    GLuint create2DTexture(const GLchar* imgPath) const;
    
    /**
     创建(2D)纹理

     @param imgPath （纹理）图片路径
     @param internalFormat 纹理（内部存储）格式
     @param pixelFormat 图片（数据类型）格式
     @return 纹理对象引用 ID
     */
    GLuint createTexture(const GLchar* imgPath, GLint internalFormat, GLenum pixelFormat) const;
    
    /**
     创建(3D)纹理
     
     @param cubImgPaths 所有(6 个 纹理)图片路径
     @return 纹理对象引用 ID
     */
    GLuint create3DTexture(std::vector<std::string> cubImgPaths);
    
public:
    /**
     创建 2D 纹理构造函数
     
     @param imgPath 纹理图像路径
     */
    Texture(const GLchar* imgPath);
    
    /**
     创建 2D 纹理构造函数
     
     @param imgPath 纹理图像路径
     @param internalFormat 纹理（内部存储）格式
     @param pixelFormat 图片（数据类型）格式
     */
    Texture(const GLchar* imgPath, GLint internalFormat, GLenum pixelFormat);
    
    /**
     创建 3D(立方体) 纹理构造函数
     
     @param cubImgPaths 立方体所有(6 个)纹理路径
     */
    Texture(std::vector<std::string> cubImgPaths);
    
    ~Texture();
    
    /**
     设置(2D)纹理环绕方式

     @param sWrap S 轴环绕方式
     @param tWrap T 轴环绕方式
     */
    void set2DWrap(GLint sWrap, GLint tWrap) const;
    
    /**
     设置(3D)纹理环绕方式
     
     @param sWrap S 轴环绕方式
     @param tWrap T 轴环绕方式
     @param rWrap R 轴环绕方式
     */
    void set3DWrap(GLint sWrap, GLint tWrap, GLint rWrap) const;
    
    /**
     设置(2D)纹理过滤方式

     @param minFilter 缩小 过滤方式
     @param magFilter 放大 过滤方式
     */
    void set2DFilter(GLint minFilter, GLint magFilter) const;
    
    /**
     设置(3D)纹理过滤方式
     
     @param minFilter 缩小 过滤方式
     @param magFilter 放大 过滤方式
     */
    void set3DFilter(GLint minFilter, GLint magFilter) const;
    
    /**
     获取(2D)纹理对象 ID

     @return 纹理对象引用 ID
     */
    GLuint texture2DId() const;
    
    /**
     获取(3D)纹理对象 ID
     
     @return 纹理对象引用 ID
     */
    GLuint texture3DId() const;
    
    /**
     激活并绑定(2D)纹理到指定的纹理单元

     @param unit 纹理单元（'GL_TEXTURE0' —— 'GL_TEXTUREMaxUnit'）
     */
    void use2D(GLenum unit) const;
    
    /**
     激活并绑定(3D)纹理到指定的纹理单元
     
     @param unit 纹理单元（'GL_TEXTURE0' —— 'GL_TEXTUREMaxUnit'）
     */
    void use3D(GLenum unit) const;
    
    /**
     释放(2D)纹理
     */
    void free2DTexture();
    
    /**
     释放(3D)纹理
     */
    void free3DTexture();
};

#endif /* Texture_hpp */
