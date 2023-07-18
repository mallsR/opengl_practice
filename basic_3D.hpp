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

//  函数声明区域
//------------------------
void mouse_callback(GLFWwindow * window, double x_pos, double y_pos);

class Basic3D : public Parallelogram {
protected:
    glm::vec3 camera_pos;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
public:
    Basic3D(string out_vertex_shader_source = "", string out_fragment_shader_source = "", int width = 800, int height = 600, const char * window_name = "create_window");
//    vertex shader & fragment shader confirgulation, compile shaderprogram
    bool setShaderProgram();
    void setTexture();
//    prepare data
    void prepareDataBuffer(float out_vertices[] = {}, int out_vertices_arr_len = 0);
//  mvp transformation : local space -> world space -> view space -> clip space -> screen space
    glm::mat4 setModelMatrix(glm::vec3 cube_position = {});
    glm::mat4 setViewMatrix(glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 0.3f));
    glm::mat4 setProjectionMatrix();
    void setMVP();
    int draw(float out_vertices[] = {}, int out_vertices_arr_len = 0);
    
//    友元函数
    friend void setCamera();
};

#endif /* basic_3D_hpp */
