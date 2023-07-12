//
//  basic_graph.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/11.
//

#include "basic_graph.hpp"

BasicGraph::BasicGraph(int width, int height, const char * window_name) {
    width_ = width;
    height_ = height;
    window_name_ = window_name;
}

void BasicGraph::initGLFW() {
//    glfw init and configurate
//    -------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}

bool BasicGraph::createWindow()  {
    initGLFW();
//    create glfw window
//    ------
    window_ = glfwCreateWindow(width_, height_, window_name_, NULL, NULL);
    if(window_ == NULL) {
        cout<<"Failed to create GLFW window."<<endl;
        glfwTerminate();
        return false;
    }
//    通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window_);
//    注册函数framebuffer_size_callback函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数：
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
    return true;
}

int BasicGraph::setGLAD() {
//    设置glad，管理opengl函数的指针
//    ------
//    给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout<<"Failed to initialize LAD"<<endl;
        return -1;
    }
    return 0;
}

int BasicGraph::draw() {
//    创建窗口
    if (!createWindow()) {
        return -1;
    }
//    设置glad
    if(setGLAD() == -1) {
        return -1;
    }
    std::cout << "draw successfully."  << std::endl;
    while (!glfwWindowShouldClose(window_)) {
//        处理输入
        processIuput(window_);
//        渲染指令
//        glClearColor,设置清空屏幕所用的颜色,只是设置状态
        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);
//        交换缓冲区
        glfwSwapBuffers(window_);
//        处理触发事件
        glfwPollEvents();
    }
    return 0;
}

//函数定义区域
//统一处理输入
//----------
void processIuput(GLFWwindow * window) {
//    按下ESC键
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//        设置窗口状态为关闭
        glfwSetWindowShouldClose(window, true);
    }
}

//设置视口大小
//----------
void framebuffer_size_callback(GLFWwindow * window, int width, int  height) {
//    通过调用glViewport函数，设置窗口维度
//    para_0, para_1，设置窗口左下角的位置，para_2,para_3设置窗口宽高
    glViewport(0, 0, width, height);
}

