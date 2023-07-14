//
//  main.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/10.
//

#include "basic_graph.hpp"
#include "draw_triangle.hpp"
#include "parallelogram.hpp"
#include "shader.hpp"

int main() {
//    定义基础图形类
//    BasicGraph *  basic_graph_obj = new BasicGraph();
//    int basic_flag = basic_graph_obj->draw();
//    if(basic_flag) {
//        cout << "ERROR::BasicGraph::draw" << endl;
//    }
//    delete basic_graph_obj;
//    定义三角形类
//    Triangle * triangle = new Triangle();
//    int flag = triangle->draw();
//    if(flag) {
//        cout << "ERROR::Triangle::draw" << endl;
//    }
//    delete triangle;
//    定义平行四边形类
//    Parallelogram * parallelogram = new Parallelogram();
//    int parallelogram_flag = parallelogram->draw();
//    if (parallelogram_flag) {
//        cout << "ERROR::Parallelogram::draw" << endl;
//    }
//    delete parallelogram;
//    use class shader
//    glfw init and configuration
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    #ifdef __APPLE__
//        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    #endif
////    create glfw window
//    GLFWwindow * window = glfwCreateWindow(800, 600, "use class shader", NULL, NULL);
//    if(window == NULL) {
//        cout<<"Failed to create GLFW window."<<endl;
//        glfwTerminate();
//        return -1;
//    }
////    设置当前线程上下文
//    glfwMakeContextCurrent(window);
////
////    配置glad
    Shader our_shader("33shader_vs.txt", "33shader_fs.txt");
    our_shader.draw();
//    while (!glfwWindowShouldClose(our_shader.getWindow())) {
////        处理输入
//        processIuput(our_shader.getWindow());
////        使用program
//        our_shader.use();
//        our_shader.draw();
//        glfwSwapBuffers(our_shader.getWindow());
//        glfwPollEvents();
//    }
//    glDeleteProgram(our_shader.ID);
//    glfwTerminate();
    return 0;
}

