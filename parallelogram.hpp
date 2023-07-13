//
//  parallelogram.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/12.
//

#ifndef parallelogram_hpp
#define parallelogram_hpp

#include <stdio.h>
#include "basic_graph.hpp"

class Parallelogram : public BasicGraph{
private:
    unsigned int VBO;
    unsigned int EBO;
    unsigned int VAO;
public:
    Parallelogram(int width = 800, int height = 600, const char * window_name = "create_window");
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
//    prepare data buffer
    void prepareDataBuffer();
//    recycle resource
    void recycleResource();
    int draw();
};

#endif /* parallelogram_hpp */
