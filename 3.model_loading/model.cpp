//
//  model.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/31.
//

#include "model.hpp"

// 从文件加载纹理
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

/* 加载模型 */
void Model::loadModel(string path) {
    Assimp::Importer import;
//    aiProcess_Triangulate : 将模型所有的图元形状变为三角形
//    aiProcess_FlipUVs : 在处理的时候翻转y轴的纹理坐标
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

//    如果场景或其根节点为空，或者返回的数据不完整（通过flag标记识别），则加载模型失败
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    
//    获取模型目录
    directory = path.substr(0, path.find_last_of('/'));

//    递归地处理节点，优先处理根节点，然后处理根节点的子节点们
    processNode(scene->mRootNode, scene);
}

// 处理节点
//------------------------
void Model::processNode(aiNode *node, const aiScene *scene)
{
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // 接下来对它的子节点重复这一过程
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

// 处理mesh 将一个aiMesh对象转化为我们自己的网格对象，包含三部分工作：
// 获取所有的顶点数据，获取它们的网格索引，并获取相关的材质数据。
//-------------------------------------------------------------------------
Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
//    分别存储顶点、索引和纹理
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
//    1、处理顶点数据
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // 处理顶点位置、法线和纹理坐标
//        使用glm::vec3 vector;临时变量的原因是Assimp对向量、矩阵、字符串等都有自己的一套数据类型，
//        它们并不能完美地转换到GLM的数据类型中。
//        处理顶点位置
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
//        处理法线
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
//        处理纹理坐标
        if(mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }
    // 2、处理索引 : 遍历所有的面，并储存了面的索引到indices这个vector中
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // 3、处理材质 ： 网格材质索引位于它的mMaterialIndex属性中，我们同样可以用它来检测一个网格是否包含有材质：
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material,
                                            aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        vector<Texture> specularMaps = loadMaterialTextures(material,
                                            aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

// 加载纹理 ： 遍历了给定纹理类型的所有纹理位置，获取了纹理的文件位置，并加载并和生成了纹理，将信息储存在了一个Vertex结构体中。它看起
//-----------------------------
vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
//    GetTextureCount函数检查储存在材质中纹理的数量，这个函数需要一个纹理类型
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
//        GetTexture获取每个纹理的文件位置，它会将结果储存在一个aiString中
        mat->GetTexture(type, i, &str);
        Texture texture;
//        TextureFromFile的工具函数，它将会（用stb_image.h）加载一个纹理并返回该纹理的ID。
        texture.id = TextureFromFile(str.C_Str(), directory);
        texture.type = typeName;
//        texture.path = str;
        textures.push_back(texture);
    }
    return textures;
}


// 从文件加载纹理
//-------------------
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

// 绘制模型 ： 依次调用mesh的Draw函数
//----------------------------
void Model::Draw(Shader shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Draw(shader);
}

