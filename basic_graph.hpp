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
    char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
//    fragment shader hard code
    char * fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 ourColor;  //在opengl代码中设置这边uniform变量，实现外部改变起功能\n"
        "void main()\n"
        "{\n"
        "   // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "   FragColor = ourColor;\n"
        "} \n\0";
public:
    BasicGraph(int width = 800, int height = 600, const char * window_name = "create_window");
    void initGLFW();
    bool createWindow();
    int setGLAD();
    bool setVertexShader(char * vertexShaderSource);
    bool setFragmentShader(char * fragmentShaderSource);
    bool setShaderProgram();
    float setWindowColor();
    void recycleResource();
    int draw();
};

#endif /* basic_graph_hpp */
