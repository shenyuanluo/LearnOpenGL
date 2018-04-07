//
//  Transform.hpp
//  Transformations
//
//  Created by shenyuanluo on 2017/8/14.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

/*
 ========= 变换 =========
 注意，矩阵乘法是不遵守交换律的，这意味着它们的顺序很重要。建议在组合矩阵时，
 先进行缩放操作，然后是旋转，最后才是位移，否则它们会（消极地）互相影响。
 【当矩阵相乘时，在最右边的矩阵是第一个与向量相乘的；应该从右向左读这个乘法。】
 （记住，实际的变换顺序应该与阅读顺序相反：尽管在代码中我们先位移再旋转，实际的变换却是先应用旋转再是位移的。）
 
 变换顺序：【缩放 ——> 旋转 ——> 位移】
 */

#ifndef Transform_hpp
#define Transform_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>


class Transform
{
private:
    glm::mat4 m_transformMat;   /* 变换矩阵 */
    
public:
    Transform();
    
    ~Transform();
    
    /**
     平移（矩阵）操作

     @param x 平移向量 x 坐标
     @param y 平移向量 y 坐标
     @param z 平移向量 z 坐标
     */
    void translate(GLfloat x, GLfloat y, GLfloat z);
    
    /**
     旋转（矩阵）操作

     @param angle 旋转角度（弧度）
     @param x 旋转向量 x 坐标
     @param y 旋转向量 y 坐标
     @param z 旋转向量 z 坐标
     */
    void rotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
    
    /**
     缩放（矩阵）操作

     @param x 缩放向量 x 坐标
     @param y 缩放向量 y 坐标
     @param z 缩放向量 z 坐标
     */
    void scale(GLfloat x, GLfloat y, GLfloat z);
    
    /**
     角度制转弧度制

     @param degree 角度制度数
     @return 弧度制度数
     */
    GLfloat radianWithDegree(GLfloat degree);
    
    /**
     使用变换矩阵

     @return （组合）变换矩阵数据
     */
    GLfloat* use();
    
    /**
     重置为单位矩阵
     */
    void reset();
    
};

#endif /* Transform_hpp */
