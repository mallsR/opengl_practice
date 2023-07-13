//
//  basic_graph.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/11.
//

#include "basic_graph.hpp"

// 顶点着色器硬代码
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// fragment shader 硬代码
const char * fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "} \n\0";

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

bool BasicGraph::setVertexShader() {
//    顶点着色器 ：vertex shader
//    ------------------------
//    创建顶点着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    将着色器源码附加到着色器对象上，并进行编译
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
//    检查编译着色器是否成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
        return false;
    }
    return true;
}

bool BasicGraph::setFragmentShader() {
//    片段着色器 : fragment shader
//    ---------------------------
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    将着色器源码附加到着色器对象上，并进行编译
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
//    检查编译着色器是否成功
    int frag_success;
    char frag_log_info[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &frag_success);
    if(!frag_success)  {
        glGetShaderInfoLog(fragmentShader, 512, NULL, frag_log_info);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << frag_log_info << endl;
        return false;
    }
    return true;
}

bool BasicGraph::setShaderProgram() {
//    着色器程序
//    --------
//    创建程序对象
    shaderProgram = glCreateProgram();
//    附加着色器到程序对象，并进行链接
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
//    检查着色器链接是否失败
    int program_success;
    char program_log_info[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &program_success);
    if(!program_success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, program_log_info);
        cout << "ERROR::PROGRAM::LINK_FAILED\n" << program_log_info << endl;
        return false;
    }
    //    删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

void BasicGraph::recycleResource() {
//    回收所有缓冲资源
//    -------------
    glDeleteProgram(shaderProgram);
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

