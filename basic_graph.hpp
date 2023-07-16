//
//  basic_graph.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/11.
//

#ifndef basic_graph_hpp
#define basic_graph_hpp

#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

//函数声明区域
//----------
void processIuput(GLFWwindow * window);
void framebuffer_size_callback(GLFWwindow * window, int width, int  height);

class BasicGraph{
private:
    int width_;
    int height_;
    const char * window_name_;
protected:
    GLFWwindow * window_;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
//    vertex shader hard code
    string vertex_shader_source;
//    fragment shader hard code
    string fragment_shader_source;
public:
    BasicGraph(string out_vertex_shader_source = "", string out_fragment_shader_source = "", int width = 800, int height = 600, const char * window_name = "create_window");
    void initGLFW();
    bool createWindow();
    int setGLAD();
    bool setVertexShader();
    bool setFragmentShader();
    bool setShaderProgram();
    float setWindowColor();
    void recycleResource();
    int draw();
};

#endif /* basic_graph_hpp */
