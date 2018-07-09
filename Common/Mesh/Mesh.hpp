//
//  Mesh.hpp
//  
//
//  Created by shenyuanluo on 2017/8/23.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "Shader.hpp"

/*
 C++结构体有个特性，它们的内存布局是连续的(Sequential)
 */
// 顶点结信息 结构体
typedef struct __vertex {
    glm::vec3 Position;     // 位置向量
    glm::vec3 Normal;       // 法向量
    glm::vec2 TexCoords;    // 纹理坐标向量
    glm::vec3 Tangent;      // 切线向量
    glm::vec3 Bitangent;    // 副切线向量
}VertexInfo;

// 纹理信息 结构体
typedef struct __texture {
    GLuint tId;             // 纹理 ID
    std::string type;       // 纹理类型（漫反射贴图：texture_diffuse、镜面光贴图：texture_specular）
    std::string path;       // 纹理图片路径（用于与其它纹理进行比较）
}TextureInfo;


class Mesh
{
private:
    // 渲染数据
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    
    // 网格数据
    std::vector<VertexInfo> m_vertices;     // 顶点
    std::vector<GLuint> m_indices;          // 索引
    std::vector<TextureInfo> m_textures;    // 纹理
    
    /**
     设置网格数据
     */
    void setupMesh();
    
public:
    
    Mesh(std::vector<VertexInfo> vertices, std::vector<GLuint> indices, std::vector<TextureInfo> textures);
    
    ~Mesh();
    
    /**
     获取网格 VAO

     @return 网格 VAO
     */
    GLuint meshVAO() const;
    
    /**
     获取网格索引
     
     @return 网格索引
     */
    std::vector<GLuint>meshIndices() const;
    
    /**
     绘制网格

     @param shader 着色器
     */
    void draw(const Shader &shader);
};

#endif /* Mesh_hpp */
