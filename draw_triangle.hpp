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
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    unsigned int VAO;
    unsigned int VBO;
public:
    Triangle(int width = 800, int height = 600, const char * window_name = "create_window");
    void initGLFW();
    bool createWindow();
    int setGLAD();
    bool setVertexShader();
    bool setFragmentShader();
    bool setShaderProgram();
    void prepareDataBuffer();
    int draw();
    void recycleResource();
};

#endif /* draw_triangle_hpp */
