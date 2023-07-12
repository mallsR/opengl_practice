//
//  draw_triangle.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/11.
//

#ifndef draw_triangle_hpp
#define draw_triangle_hpp

#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "basic_graph.hpp"
#include <string>

using namespace std;

//函数声明区域
//----------
void processIuput(GLFWwindow * window);
void framebuffer_size_callback(GLFWwindow * window, int width, int  height);

class Triangle : public BasicGraph{
private:
    int width_;
    int height_;
    const char * window_name_;
    GLFWwindow * window_;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    unsigned int VAO;
    unsigned int VBO;
public:
    void initGLFW();
    bool createWindow(int width = 800, int height = 600, const char * window_name = "create_window");
    int setGLAD();
    bool setVertexShader();
    bool setFragmentShader();
    bool setShaderProgram();
    void prepareDataBuffer();
    int draw();
    void recycleResource();
};

#endif /* draw_triangle_hpp */
