//
//  draw_triangle.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/11.
//


// 引入glad管理opengl的函数，引入glfw设置窗口，屏蔽系统细节
#include "draw_triangle.hpp"

//函数声明区域
//----------
void processIuput(GLFWwindow * window);
void framebuffer_size_callback(GLFWwindow * window, int width, int  height);

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

int Triangle::draw() {
//    glfw init and configurate
//    -------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
//    create glfw window
//    ------
    GLFWwindow * window = glfwCreateWindow(800, 600, "create_window", NULL, NULL);
    if(window == NULL) {
        cout<<"Failed to create GLFW window."<<endl;
        glfwTerminate();
        return -1;
    }
//    通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);
//    注册函数framebuffer_size_callback函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数：
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
//    设置glad，管理opengl函数的指针
//    ------
//    给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout<<"Failed to initialize LAD"<<endl;
        return -1;
    }
//    顶点着色器 ：vertex shader
//    ------------------------
//    创建顶点着色器
    unsigned int vertexShader;
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
    }
//    片段着色器 : fragment shader
//    ---------------------------
    unsigned int fragmentShader;
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
    }
//    着色器程序
//    --------
//    创建程序对象
    unsigned int shaderProgram;
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
        cout << "ERROR::PROGRAM::LINK_FAILED\n" << frag_log_info << endl;
    }
//    删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
//    设置顶点位置，并加载到顶点缓冲的内存中，方便读取
//    --------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
//    创建顶点数组对象VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
//    绑定VAO
    glBindVertexArray(VAO);
//    设置顶点缓冲对象 ： 使用glGenBuffers函数和一个缓冲ID生成一个VBO对象
    unsigned int VBO;
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
//    VBO和VAO解绑
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
//    渲染过程
//    ------
    while(!glfwWindowShouldClose(window)) {
//        处理输入
        processIuput(window);
//        渲染指令
//        glClearColor,设置清空屏幕所用的颜色,只是设置状态
        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);
//        激活程序对象
        glUseProgram(shaderProgram);
//        绑定VAO
        glBindVertexArray(VAO);
//        绘制图元
        glDrawArrays(GL_TRIANGLES, 0, 3);
//        交换缓冲区
        glfwSwapBuffers(window);
//        处理触发事件
        glfwPollEvents();
    }
//    回收所有缓冲资源
//    -------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
//    回收资源
//    -------
    glfwTerminate();
    return 0;
};

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
