//
//  basic_3D.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/17.
//

#ifndef basic_3D_hpp
#define basic_3D_hpp

#include <stdio.h>
#include "parallelogram.hpp"

class Basic3D : public Parallelogram {
public:
    Basic3D(string out_vertex_shader_source = "", string out_fragment_shader_source = "", int width = 800, int height = 600, const char * window_name = "create_window");
//    vertex shader & fragment shader confirgulation, compile shaderprogram
    bool setShaderProgram();
    void setTexture();
//    prepare data
    void prepareDataBuffer(float out_vertices[] = {}, int out_vertices_arr_len = 0);
//  mvp transformation : local space -> world space -> view space -> clip space -> screen space
    glm::mat4 setModelMatrix(glm::vec3 cube_position = {});
    void setMVP();
    int draw(float out_vertices[] = {}, int out_vertices_arr_len = 0);
};

#endif /* basic_3D_hpp */
