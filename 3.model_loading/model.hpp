//
//  model.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/31.
//

#ifndef model_hpp
#define model_hpp

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// 在使用的位置加入stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "mesh.hpp"
#include "shader.hpp"

#include <stdio.h>
#include <string>
#include <vector>

class Model
{
public:
    /*  函数   */
    Model(char *path)
    {
//            直接通过loadModel来加载文件。私有函数将会处理Assimp导入过程中的一部分，
        loadModel(path);
    }
    void Draw(Shader shader);
private:
        /*  模型数据  */
    vector<Mesh> meshes;
    string directory;
    /*  函数   */
    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

#endif /* model_hpp */
