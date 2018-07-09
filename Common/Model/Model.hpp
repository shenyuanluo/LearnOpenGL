//
//  Model.hpp
//  
//
//  Created by shenyuanluo on 2017/8/24.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Shader.hpp"
#include "Mesh.hpp"


class Model
{
private:
    std::vector<TextureInfo> m_texturesLoaded;  // 纹理（存储所有已加载的纹理，避免多次加载耗性能）
    std::vector<Mesh> m_meshes;                 // 网格
    std::string m_directory;                    // 模型文件路径的目录
    bool m_gammaCorrection;
    
    /**
     加载模型文件，存储所有网格数据

     @param path 模型文件路径
     */
    void loadModel(std::string const &path);
    
    /**
     递归处理节点

     @param node 节点
     @param scene 场景
     */
    void processNode(aiNode *node, const aiScene *scene);
    
    /**
     处理网格(Mesh)，获取顶点数据、索引、材质属性...

     @param mesh 网格对象
     @param scene 场景对象
     @return 网格(自定义)对象
     */
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    
    
    /**
     加载材质纹理数据

     @param mat 材质数据
     @param type 纹理类型
     @param typeName 纹理名称
     @return 纹理对象
     */
    std::vector<TextureInfo>loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    
    /**
     创建纹理对象

     @param path 纹理图片相对路径
     @param directory 纹理资源目录
     @param gamma gamma
     @return 纹理对象引用 ID
     */
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
    
public:
    Model(std::string const &path, bool gamma = false);
    
    ~Model();
    
    /**
     获取网格
     
     @return 网格容器
     */
    std::vector<Mesh>meshes() const;
    
    /**
     绘制模型

     @param shader 模型对应的着色器
     */
    void draw(const Shader &shader);
};

#endif /* Model_hpp */
