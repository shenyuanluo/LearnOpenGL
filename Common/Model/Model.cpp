//
//  Model.cpp
//  
//
//  Created by shenyuanluo on 2017/8/24.
//  Copyright © 2017年 http://blog.shenyuanluo.com/ All rights reserved.
//

#include "Model.hpp"
#include "Texture.hpp" 


#pragma mark - Public
#pragma mark -- 构造函数
Model::Model(std::string const &path, bool gamma) : m_gammaCorrection(gamma)
{
    loadModel(path);
}

#pragma mark -- 析构函数
Model::~Model()
{
    
}

#pragma mark - 获取网格
std::vector<Mesh>Model::meshes() const
{
    return m_meshes;
}

#pragma mark -- 绘制模型
void Model::draw(const Shader &shader)
{
    for (GLuint i = 0; i < m_meshes.size(); i++)
    {
        m_meshes[i].draw(shader);
    }
}

#pragma mark - Private
#pragma mark -- 加载模型文件，存储所有网格数据
void Model::loadModel(std::string const &path)
{
    Assimp::Importer importer;
    /* 加载模型文件到 scene 中
     aiProcess_Triangulate: 设定 Assimp， 如果模型不是(全部)由三角形组成，需要将模型的所有图元形状转变成三角形。
     aiProcess_FlipUVs: 设定 Assimp 在处理的时候翻转 Y 轴的纹理坐标(即，纹理图像上下倒转)
     aiProcess_CalcTangentSpace:
     */
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    
    if(!scene
       || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
       || !scene->mRootNode)
    {
        std::cout << "Assimp 导入模型文件失败：" << importer.GetErrorString() << std::endl;
        return;
    }
    // 保存文件路径目录
    m_directory = path.substr(0, path.find_last_of('/'));
    
    processNode(scene->mRootNode, scene);
}

#pragma mark -- 递归处理节点
void Model::processNode(aiNode *node, const aiScene *scene)
{
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }
    // 遍历所有节点，获取对应的网格(Mesh)
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

#pragma mark -- 处理网格(Mesh)，获取顶点数据、索引、材质属性...
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // 数据填充
    std::vector<VertexInfo> vertices;       // 顶点
    std::vector<unsigned int> indices;      // 索引
    std::vector<TextureInfo> textures;      // 纹理
    
    // 遍历网格中的所有顶点
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        /*
         由于 Assimp 内置的 Vector 不能直接的转换成 glm::vec3，
         所以需要进行转换
         */
        /* ============== 顶点处理 ============== */
        VertexInfo vertex;
        glm::vec3 vector;
        // 位置（Assimp 将顶点位置数组叫做 mVertices ）
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        
        // 法向量
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        
        // 纹理坐标
        if(mesh->mTextureCoords[0]) // 网格是否包含纹理坐标
        {
            glm::vec2 vec;
            /*
             Assimp允许一个模型在一个顶点上有最多 8 个不同的纹理坐标，
             暂时不会用到那么多，所以只选择第一组纹理坐标
             */
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }
        
        // 切线
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;
        
        // 副切线
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        
        // 将处理好的顶点添加到‘顶点数组’中
        vertices.push_back(vertex);
    }
    
    /* ============== 索引处理 ============== */
    /*
     Assimp 的接口定义了每个网格都有一个面(Face)数组，每个面代表了一个图元，
     一个面包含了多个索引，它们定义了在每个图元中，应该绘制哪个顶点，并以什么顺序绘制
     */
    // 索引
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // 遍历每个 Face 的所有索引并添加到‘索引数组’中
        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
    
    /* ============== 材质处理 ============== */
    // 材质
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    /*
     对于着色器中的纹理采样器(sampler)的名字做如下假定：
     （其中 N 序号表示从 1 开始 到最大支持的纹理采样器数(MAX_SAMPLER_NUMBER)）
     1. 漫反射纹理：texture_diffuseN，
     2. 镜面光纹理：texture_specularN，
     3. 发现纹理：texture_normalN
     4. 高度贴图：texture_heightN
     */
    
    // 1. 漫反射贴图
    std::vector<TextureInfo> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. 镜面光贴图
    std::vector<TextureInfo> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. 法线贴图
    std::vector<TextureInfo> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. 高度贴图
    std::vector<TextureInfo> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    
    // 解析完网格数据，创建 Mesh 对象
    return Mesh(vertices, indices, textures);
}

#pragma mark -- 加载材质纹理数据
std::vector<TextureInfo>Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<TextureInfo> textures;
    // 检查储存在材质中纹理的数量
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str); // 获取纹理文件位置
        
        // 检查纹理文件是否已经加载
        bool skip = false;
        for(unsigned int j = 0; j < m_texturesLoaded.size(); j++)
        {
            if(0 == std::strcmp(m_texturesLoaded[j].path.data(), str.C_Str()))
            {
                // 纹理文件已经加载，直接从‘已加载的纹理数组’添加到’纹理数组‘中，优化了再次加载纹理
                textures.push_back(m_texturesLoaded[j]);
                skip = true;
                break;
            }
        }
        // 纹理还没有加载
        if(!skip)
        {
            TextureInfo texture;
            texture.tId  = TextureFromFile(str.C_Str(), m_directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            m_texturesLoaded.push_back(texture);    // 存储至全局以优化重复加载纹理
        }
    }
    return textures;
}

#pragma mark -- 创建纹理对象
unsigned int Model::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;
    
    // 创建纹理
    Texture texture(filename.c_str());
    texture.set2DWrap(GL_REPEAT, GL_REPEAT);
    texture.set2DFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    
    return texture.texture2DId();
}

