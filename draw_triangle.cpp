//
//  draw_triangle.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/11.
//


// 引入glad管理opengl的函数，引入glfw设置窗口，屏蔽系统细节
#include "draw_triangle.hpp"

Triangle::Triangle(int width, int height, const char * window_name) {
    BasicGraph(width, height, window_name);
}

void Triangle::initGLFW() {
    BasicGraph::initGLFW();
}

bool Triangle::createWindow() {
    return BasicGraph::createWindow();
}

int Triangle::setGLAD() {
    return BasicGraph::setGLAD();
}

bool Triangle::setVertexShader() {
    return BasicGraph::setVertexShader();
}

bool Triangle::setFragmentShader() {
    return BasicGraph::setFragmentShader();
}

bool Triangle::setShaderProgram() {
    return BasicGraph::setShaderProgram();
}

void Triangle::prepareDataBuffer() {
//    设置顶点位置，并加载到顶点缓冲的内存中，方便读取
//    --------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
//    创建顶点数组对象VAO
    glGenVertexArrays(1, &VAO);
//    绑定VAO
    glBindVertexArray(VAO);
//    设置顶点缓冲对象 ： 使用glGenBuffers函数和一个缓冲ID生成一个VBO对象
    glGenBuffers(1, &VBO);
//    绑定缓冲到GL_ARRAY_BUFFER目标上
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    顶点数据复制到缓冲的内存
//    para_4 : 显卡如何管理数据 使用的类型就是GL_DYNAMIC_DRAW或GL_STREAM_DRAW，这样就能确保显卡把数据放在能够高速写入的内存部分
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    链接顶点属性 ：用于告知OpenGL以何种方式解析和利用内存中的顶点数据
//    ------------------------------------------------------
//    设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void *)0);
//    顶点属性位置值作为参数，启用顶点属性；
    glEnableVertexAttribArray(0);
//    VBO和VAO解绑:此处解绑VAO是为了避免其他偶然性的事件修改这个VAO的内容
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return ;
}

void Triangle::recycleResource() {
//    回收所有缓冲资源
//    -------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    BasicGraph::recycleResource();
}

int Triangle::draw() {
//    创建窗口
    if (!createWindow()) {
        return -1;
    }
//    设置glad
    if(setGLAD() == -1) {
        return -1;
    }
//    设置顶点着色器
    if(!setVertexShader()) {
        return -1;
    }
//    设置片段着色器
    if(!setFragmentShader()) {
        return -1;
    }
//    设置着色器程序
    if(!setShaderProgram()) {
        return -1;
    }
//    设置数据缓冲
    prepareDataBuffer();
//    渲染过程
//    ------
    while(!glfwWindowShouldClose(window_)) {
//        处理输入
        processIuput(window_);
//        渲染指令
//        glClearColor,设置清空屏幕所用的颜色,只是设置状态
        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);
//        在窗口内底色上，绘制三角形
//        激活程序对象
        glUseProgram(shaderProgram);
//        绑定VAO
        glBindVertexArray(VAO);
//        绘制图元
        glDrawArrays(GL_TRIANGLES, 0, 3);
//        交换缓冲区
        glfwSwapBuffers(window_);
//        处理触发事件
        glfwPollEvents();
    }
    recycleResource();
//    回收资源
//    -------
    glfwTerminate();
    return 0;
};

//函数定义区域
//统一处理输入
//----------
//void processIuput(GLFWwindow * window) {
////    按下ESC键
//    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
////        设置窗口状态为关闭
//        glfwSetWindowShouldClose(window, true);
//    }
//}
