//
//  parallelogram.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/12.
//

#ifndef parallelogram_hpp
#define parallelogram_hpp

#include "basic_graph.hpp"
#include <string.h>
// 使用GLM
#include "glm-0.9.8.5/glm/glm.hpp"
#include "glm-0.9.8.5/glm/gtc/matrix_transform.hpp"
#include "glm-0.9.8.5/glm/gtc/type_ptr.hpp"

// 函数定义区域

class Parallelogram : public BasicGraph{
protected:
    unsigned int VBO;
    unsigned int EBO;
    unsigned int VAO;
    unsigned int texture1;
    unsigned int texture2;
public:
    Parallelogram(string out_vertex_shader_source = "", string out_fragment_shader_source = "", int width = 800, int height = 600, const char * window_name = "create_window");
//    glfw : init and configurature
    bool createWindow();
//    glad : origanize opengl functions
    int setGLAD();
//    vertex shader
    bool setVertexShader();
//    fragment shader
    bool setFragmentShader();
//    shader program
    bool setShaderProgram();
    void setTexture();
    glm::mat4 setTransformation();
    glm::mat4 setModelMatrix();
    glm::mat4 setViewMatrix();
    glm::mat4 setProjectionMatrix();
//    prepare data buffer
    void prepareDataBuffer(float out_vertices[] = {}, int out_vertices_arr_len = 0);
//    recycle resource
    void recycleResource();
    int draw(float out_vertices[] = {}, int out_vertices_arr_len = 0);
};

#endif /* parallelogram_hpp */
