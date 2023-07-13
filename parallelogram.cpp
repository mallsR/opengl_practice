//
//  parallelogram.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/12.
//

#include "parallelogram.hpp"

Parallelogram::Parallelogram(int width, int height, const char * window_name) {
    BasicGraph(width, height, window_name);
}

bool Parallelogram::createWindow() {
    return BasicGraph::createWindow();
}

int Parallelogram::setGLAD() {
    return BasicGraph::setGLAD();
}

bool Parallelogram::setVertexShader() {
    return BasicGraph::setVertexShader(vertexShaderSource);
}

bool Parallelogram::setFragmentShader() {
    return BasicGraph::setFragmentShader(fragmentShaderSource);
}

bool Parallelogram::setShaderProgram() {
    return BasicGraph::setShaderProgram();
}

void Parallelogram::prepareDataBuffer() {
//    绘制矩形所需的点和索引
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };
    unsigned int indices[] = {
        // 注意索引从0开始!
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形

        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
//    创建顶点数组对象，并进行绑定
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
//    创建顶点缓冲对象，并进行绑定，复制数据到顶点缓冲中，供opengl使用
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    创建索引缓冲对象，并进行绑定，复制索引到索引缓冲中，供opengl使用
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//    设置顶点属性指针，告知opengl该如何解析这些数据，并启用顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
//    note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    但是EBO是不能解绑的，在VAO解绑定之前。因为glVertexAttribPointer只是将顶点的信息放入了VAO之中，而索引的信息是没有放入的，还是需要从GL_ELEMENT_ARRAY_BUFFER中取。
    glBindVertexArray(0);
}

void Parallelogram::recycleResource() {
//    函数VAO、VBO、EBO;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
//    删除shader program
    BasicGraph::recycleResource();
}

int Parallelogram::draw() {
//    初始化glfw
    if(!createWindow()) {
        return -1;
    }
//    配置glad
    if(setGLAD() == -1) {
        return -1;
    }
//    vertex shader
    if(!setVertexShader()) {
        return -1;
    }
//    fragment shader
    if(!setFragmentShader()) {
        return -1;
    }
//    shader program
    if(!setShaderProgram()) {
        return -1;
    }
    prepareDataBuffer();
//    设置线框模式 Wireframe mode
//    para_1 : 绘制的位置
//    para_2 : 绘制方式
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window_)) {
//        处理输入
        processIuput(window_);
//        渲染指令
//        绘图之前设置背景颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
//        设定使用我们的程序进行渲染
        glUseProgram(shaderProgram);
//        在绑定VAO时，绑定的最后一个元素缓冲区对象存储为VAO的元素缓冲区对象。然后，绑定到VAO也会自动绑定该EBO。
        glBindVertexArray(VAO);
//        para_1 : 绘制的模式
//        para_2 : 绘制顶点的个数，这里填6
//        para_3 : 索引的类型，这里是GL_UNSIGNED_INT
//        para_4 : 指定EBO中的偏移量（或者传递一个索引数组，但是这是当你不在使用索引缓冲对象的时候）
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        交换缓冲区
        glfwSwapBuffers(window_);
//        查询事件并处理 ： 包括键盘和鼠标的移动等
        glfwPollEvents();
    }
    recycleResource();
    glfwTerminate();
    return 0;
}
