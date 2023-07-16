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

// 函数定义区域

class Parallelogram : public BasicGraph{
private:
    unsigned int VBO;
    unsigned int EBO;
    unsigned int VAO;
    unsigned int texture;
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
//    prepare data buffer
    void prepareDataBuffer(float out_vertices[] = {}, int out_vertices_arr_len = 0);
//    recycle resource
    void recycleResource();
    int draw();
};

#endif /* parallelogram_hpp */
