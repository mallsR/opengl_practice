//
//  mesh.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/31.
//

#ifndef mesh_hpp
#define mesh_hpp

#include "shader.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

// define vertex
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

// define texture
struct Texture {
    unsigned int id;
    string type;
};

class Mesh {
    public:
        /*  网格数据  */
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        /*  函数  */
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(Shader shader);
    private:
        /*  渲染数据  */
        unsigned int VAO, VBO, EBO;
        /*  函数  */
        void setupMesh();
};

#endif /* mesh_hpp */
