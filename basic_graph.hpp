////
////  basic_graph.hpp
////  opengl_test
////
////  Created by xiaoR on 2023/7/11.
////
//
//#ifndef basic_graph_hpp
//#define basic_graph_hpp
//
//#include <stdio.h>
//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//// 使用GLM
//#include "glm-0.9.8.5/glm/glm.hpp"
//#include "glm-0.9.8.5/glm/gtc/matrix_transform.hpp"
//#include "glm-0.9.8.5/glm/gtc/type_ptr.hpp"
//
//using namespace std;
//
////函数声明区域
////----------
////glm::vec3 processIuput(GLFWwindow * window, float & last_time,
////                  glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f,  3.0f),
////                  glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f),
////                  glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f,  0.0f));
////void framebuffer_size_callback(GLFWwindow * window, int width, int  height);
//
//class BasicGraph{
//private:
//    float width_;
//    float height_;
//    const char * window_name_;
//protected:
//    GLFWwindow * window_;
//    unsigned int vertexShader;
//    unsigned int fragmentShader;
//    unsigned int shaderProgram;
////    vertex shader hard code
//    string vertex_shader_source;
////    fragment shader hard code
//    string fragment_shader_source;
//public:
//    BasicGraph(string out_vertex_shader_source = "", string out_fragment_shader_source = "", int width = 800, int height = 600, const char * window_name = "create_window");
//    float getWidth();
//    float getHeight();
//    void initGLFW();
//    bool createWindow();
//    int setGLAD();
//    bool setVertexShader();
//    bool setFragmentShader();
//    bool setShaderProgram();
//    float setWindowColor();
//    void recycleResource();
//    int draw();
//    
////    友元函数
//};
//
//#endif /* basic_graph_hpp */
