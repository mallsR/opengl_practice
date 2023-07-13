//
//  draw_triangle.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/11.
//

#ifndef draw_triangle_hpp
#define draw_triangle_hpp

#include <string>
#include "basic_graph.hpp"

using namespace std;

//void processIuput(GLFWwindow * window);

class Triangle : public BasicGraph{
private:
    unsigned int VAO;
    unsigned int VBO;
protected:
//    vertex shader hard code
    char * vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为 0\n"
        "layout (location = 1) in vec3 aColor; // 颜色变亮的属性位置值为 1\n"
        "out vec3 ourColor; //为fragment shader输出一个颜色\n"
        "void main() {\n"
        "    gl_Position = vec4(aPos, 1.0);\n"
        "    ourColor = aColor;\n"
        "}\n";
//    fragment shader hard code
    char * fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "void main()  {\n"
        "   FragColor = vec4(ourColor, 1.0);\n"
        "}\n";
public:
    Triangle(int width = 800, int height = 600, const char * window_name = "create_window");
    void initGLFW();
    bool createWindow();
    int setGLAD();
    bool setVertexShader();
    bool setFragmentShader();
    bool setShaderProgram();
//    为缓冲准备数据
    void prepareDataBuffer();
//    设置三角形的颜色
    void setGraphColor();
    int draw();
    void recycleResource();
};

#endif /* draw_triangle_hpp */
