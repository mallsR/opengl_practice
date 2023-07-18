//
//  shader.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/14.
//

#include "shader.hpp"

Shader::Shader(const char * vertex_path, const char * fragment_path) {
//    初始化glfw 和 配置glad
    BasicGraph::createWindow();
    BasicGraph::setGLAD();
//    1、从文件中获取着色器
    string vertex_code;
    string fragment_code;
    ifstream vertex_shader_file;
    ifstream fragment_shader_file;
    // 保证ifstream对象可以抛出异常：
    vertex_shader_file.exceptions (ifstream::failbit | ifstream::badbit);
    fragment_shader_file.exceptions (ifstream::failbit | ifstream::badbit);
    try
    {
        // 打开文件
        vertex_shader_file.open(vertex_path);
        fragment_shader_file.open(fragment_path);
        stringstream vertext_shader_stream, fragment_shader_stream;
        // 读取文件的缓冲内容到数据流中
        vertext_shader_stream << vertex_shader_file.rdbuf();
        fragment_shader_stream << fragment_shader_file.rdbuf();
        // 关闭文件处理器
        vertex_shader_file.close();
        fragment_shader_file.close();
        // 转换数据流到string
        vertex_code  = vertext_shader_stream.str();
        fragment_code = fragment_shader_stream.str();
    }
    catch(ifstream::failure& e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << e.what() << endl;
    }
    const char * vertex_shader_code = vertex_code.c_str();
    const char * fragment_shader_code = fragment_code.c_str();
//    const char * vertex_shader_code = vertexShaderSource;
//    const char * fragment_shader_code = fragmentShaderSource;
//    2、编译和链接着色器，并进行检测
    unsigned int vertex_shader;
    unsigned int fragment_shader;
    int success;
    char info_log[512];
//    fragment shader
//    顶点着色器
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
    glCompileShader(vertex_shader);
//    如果编译错误，进行打印
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log <<  endl;
    }
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment_shader);
//    如果编译错误，打印输出
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log <<  endl;
    }
//    shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, fragment_shader);
    glLinkProgram(ID);
//    如果链接错误，打印错误
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID, 512, NULL, info_log);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << endl;
    }
//    删除不需要的着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const string &name, bool value) const {
//    获取uniform变量的位置，并对变量进行设置
    glUniform1i(glGetUniformLocation(ID, name.c_str()), int(value));
}

void Shader::setInt(const string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::draw() {
    float last_time = 0.0f;
    while (!glfwWindowShouldClose(window_)) {
        processIuput(window_, last_time);
        glClearColor(0.2f, setWindowColor(), 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
    glDeleteProgram(ID);
    glfwTerminate();
}

