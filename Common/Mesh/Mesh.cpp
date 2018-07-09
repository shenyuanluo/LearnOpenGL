//
//  Mesh.cpp
//  
//
//  Created by shenyuanluo on 2017/8/23.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Mesh.hpp"

#pragma mark - Public
#pragma mark -- 构造函数
Mesh::Mesh(std::vector<VertexInfo> vertices, std::vector<GLuint> indices, std::vector<TextureInfo> textures)
{
    m_vertices = vertices;
    m_indices  = indices;
    m_textures = textures;
    
    setupMesh();
}

#pragma mark -- 析构函数
Mesh::~Mesh()
{
    
}

#pragma mark - 获取网格 VAO
GLuint Mesh::meshVAO() const
{
    return m_VAO;
}

#pragma mark - 获取网格索引
std::vector<GLuint>Mesh::meshIndices() const
{
    return m_indices;
}

#pragma mark -- 绘制网格
/*
 设定一个命名标准：
 每个漫反射纹理被命名为：texture_diffuseN，
 每个镜面光纹理应该被命名为：texture_specularN，
 其中 N 的范围是 1 到纹理采样器最大允许的数字。
 */
void Mesh::draw(const Shader &shader)
{
    GLuint diffuseNr  = 1;
    GLuint specularNr = 1;
    GLuint normalNr   = 1;
    GLuint heightNr   = 1;
    
    for (GLuint i = 0; i < m_textures.size(); i++)
    {
        // 在绑定之前先激活响应的纹理单元
        glActiveTexture(GL_TEXTURE0 + i);
        // 获取纹理序号（texture_diffuseN 中的 N）
        std::string number;
        std::string name = m_textures[i].type;
        // 转换：数字 ——> 字符
        if ("texture_diffuse" == name)          // 漫反射纹理
        {
            number = std::to_string(diffuseNr++);
        }
        else if ("texture_specular" == name)    // 镜面光纹理
        {
            number = std::to_string(specularNr++);
        }
        else if ("texture_normal" == name)      // 法线纹理
        {
            number = std::to_string(normalNr++);
        }
        else if ("texture_height" == name)      // 高度纹理
        {
            number = std::to_string(heightNr++);
        }
        
        // 设置纹理单元序号
        shader.setUniformInt((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, m_textures[i].tId);
    }
    
    // 绘制网格
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    // 设置回默认值
    glActiveTexture(GL_TEXTURE0);
}


#pragma mark - Private
#pragma mark -- 设置网格数据
void Mesh::setupMesh()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    
    glBindVertexArray(m_VAO);
    
    // 顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(VertexInfo), &m_vertices[0], GL_STATIC_DRAW);
    
    // 索引数据
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);
    
    /*
     结构体预处理指令 offsetof(s, m)，第一个参数是一个结构体，第二个参数是这个结构体中变量的名字。
     这个宏会返回那个变量距结构体头部的字节偏移量(Byte Offset)。
     */
    // 顶点位置属性
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)offsetof(VertexInfo, Position));
    
    // 顶点法线属性
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void *)offsetof(VertexInfo, Normal));
    
    // 纹理坐标
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)offsetof(VertexInfo, TexCoords));
    
    // 纹理切线
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)offsetof(VertexInfo, Tangent));
    
    // 纹理双切线
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)offsetof(VertexInfo, Bitangent));
    
    // 解绑 VOA
    glBindVertexArray(0);
}


