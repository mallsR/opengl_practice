////
////  parallelogram.cpp
////  opengl_test
////
////  Created by xiaoR on 2023/7/12.
////
//
//#include "parallelogram.hpp"
//// 在使用的位置加入stb_image.h
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
////#include <dirent.h>
//#include <unistd.h>
//
//Parallelogram::Parallelogram(string out_vertex_shader_source, string  out_fragment_shader_source, int width, int height, const char * window_name) {
//    BasicGraph(out_vertex_shader_source, out_fragment_shader_source, width, height, window_name);
//    if (out_vertex_shader_source != "") {
//        vertex_shader_source = out_vertex_shader_source;
//    }
//    if (out_fragment_shader_source != "") {
//        fragment_shader_source = out_fragment_shader_source;
//    }
////    float inner_vertexs[] = {
////        0.5f, 0.5f, 0.0f,  // 右上角
////        0.5f, -0.5f, 0.0f, // 右下角
////        -0.5f, -0.5f, 0.0f, // 左下角
////        -0.5f, 0.5f, 0.0f   // 左上角
////    };
////    unsigned int inner_indices[] = {
////        // 注意索引从0开始!
////        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
////        // 这样可以由下标代表顶点组合成矩形
////
////        0, 1, 3, // 第一个三角形
////        1, 2, 3  // 第二个三角形
////    };
//}
//
//bool Parallelogram::createWindow() {
//    return BasicGraph::createWindow();
//}
//
//int Parallelogram::setGLAD() {
//    return BasicGraph::setGLAD();
//}
//
//bool Parallelogram::setVertexShader() {
//    return BasicGraph::setVertexShader();
////    if(out_vertex_shader_source) {
////        vertex_shader_source = out_vertex_shader_source;
////    }
////    vertexShader = glCreateShader(GL_VERTEX_SHADER);
////    glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
////    glCompileShader(vertexShader);
////    int success;
////    char info_log[512];
////    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
////    if(!success) {
////        glGetShaderInfoLog(vertexShader, 512, NULL, info_log);
////        cout << "ERROR::Parallelogram::setVertexShader::SHADER::Vertex::Compile::failed." << endl;
////        return false;
////    }
////    return true;
//}
//
//bool Parallelogram::setFragmentShader() {
//    return BasicGraph::setFragmentShader();
//////    片段着色器 : fragment shader
//////    ---------------------------
////    if(out_fragment_shader_source) {
////        fragment_shader_source = out_fragment_shader_source;
////    }
////    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//////    将着色器源码附加到着色器对象上，并进行编译
////    glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
////    glCompileShader(fragmentShader);
//////    检查编译着色器是否成功
////    int frag_success;
////    char frag_log_info[512];
////    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &frag_success);
////    if(!frag_success)  {
////        glGetShaderInfoLog(fragmentShader, 512, NULL, frag_log_info);
////        cout << "ERROR::Parallelogram::setVertexShader::SHADER::FRAGMENT::COMPILATION_FAILED\n" << frag_log_info << endl;
////        return false;
////    }
////    return true;
//}
//
//bool Parallelogram::setShaderProgram() {
//    return BasicGraph::setShaderProgram();
//}
//
//void Parallelogram::setTexture() {
//    glGenTextures(1, &texture1);
////    绑定纹理到当前激活的纹理单元
//    glBindTexture(GL_TEXTURE_2D, texture1);
//    // 为当前绑定的纹理对象设置环绕、过滤方式
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    加载图片
//    string WORK_DIR = "/Users/xiaor/Project/xCode/opengl_test/opengl_test/";
//    string picture1 = "container.jpg";
//    string picture_path = WORK_DIR + picture1;
//    int width, height, nrChannels;
////    char * buffer;
//////    获取当前工作目录
////    if((buffer = getcwd(NULL, 0)) == NULL) {
////        cout << "getcwd error." << endl;
////    } else {
////        cout << "buffer : " << buffer << endl;
////    }
//    unsigned char *data = stbi_load(picture_path.c_str(), &width, &height, &nrChannels, 0);
//    if(data) {
////    加载并生成纹理
////        cout << "load texture1 successfully. " << endl;
////        cout << "width : " << width << " height : " << height << " nrChannels : " << nrChannels << endl;
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    } else {
//        cout << "Failed to load texture1" << endl;
//    }
////    释放图像内存
//    stbi_image_free(data);
////    生成纹理对象
//    glGenTextures(1, &texture2);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//    // 为当前绑定的纹理对象设置环绕、过滤方式
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    加载图片 : 纹理上下颠倒！是因为OpenGL要求y轴0.0坐标是在图片的底部的，但是图片的y轴0.0坐标通常在顶部。可以使用stb_image.h库的stbi_set_flip_vertically_on_load函数翻转y轴
//    stbi_set_flip_vertically_on_load(true);
//    string picture2 = "awesomeface.png";
//    picture_path = WORK_DIR + picture2;
//    data = stbi_load(picture_path.c_str(), &width, &height, &nrChannels, 0);
//    if (data) {
////        使用加载的图片生成纹理
////        cout << "load texture2 successfully. " << endl;
////        cout << "width : " << width << " height : " << height << " nrChannels : " << nrChannels << endl;
////       my error 1
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    } else {
//        cout << "Failed to load texture2" << endl;
//    }
//    stbi_image_free(data);
////    告诉opengl，每个采样器属于哪个纹理单元 : 一定不能忘记！！！my error 2
////    activate shaderprogram
//    glUseProgram(shaderProgram);
//    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
//    glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
//}
//
//glm::mat4 Parallelogram::setTransformation() {
////    设置组合变换矩阵并返回
////    4 * 4 的单位矩阵
//    glm::mat4 trans;
//////    构建rotate matrix : 沿z轴旋转90度。 radians : 将角度转弧度（GLM想要弧度制输入）
////    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
//////    每个轴缩放0.5倍
////    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
////    随时间变化而逆时针旋转
////    但矩阵是按顺序组合的，这样相当于 trans = translate_mat * rotate_mat : 先旋转再变换
//    trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0.0));
//    trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
//    return trans;
//}
//
//glm::mat4 Parallelogram::setModelMatrix() {
//    glm::mat4 model;
////    沿着x轴，逆时针旋转55度
////    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
////    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
//    model = glm::rotate(model, (float)glfwGetTime() , glm::vec3(0.5f, 1.0f, 0.0f));
//    return model;
//}
//
//glm::mat4 Parallelogram::setViewMatrix() {
//    glm::mat4 view;
//    // 注意，我们将矩阵向我们要进行移动场景的反方向移动。
////    将场景沿着-z方向移动3个单位
//    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//    return view;
//}
//
//glm::mat4 Parallelogram::setProjectionMatrix() {
//    float screenWidth = getWidth();
//    float screenHeight = getHeight();
//    glm::mat4 projection;
//    projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
//    return projection;
//}
//
//void Parallelogram::prepareDataBuffer(float out_vertices[], int out_vertices_arr_len) {
////    默认的顶点数据和索引
//    float vertices[] = {
////        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//    };
//    unsigned int indices[] = {
//        // 注意索引从0开始!
//        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
//        // 这样可以由下标代表顶点组合成矩形
//
//        0, 1, 3, // 第一个三角形
//        1, 2, 3  // 第二个三角形
//    };
////    创建顶点数组对象，并进行绑定
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
////    创建顶点缓冲对象，并进行绑定，复制数据到顶点缓冲中，供opengl使用
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
////    cout << "sizeof(out_vertices) : " << sizeof(out_vertices)  << endl;
////    cout << "sizeof(vertices) : " << sizeof(vertices)  << endl;
////    cout << "out_vertices_arr_len * sizeof(float) : " << out_vertices_arr_len * sizeof(float) << endl;
////    如果外部传入顶点数据，则使用外部的数据
//    if (out_vertices_arr_len > 1) {
//        cout << "use out_vertices. " << endl;
////        my error 2 : sizeof(out_vertices) 并不会计算整个数组的大小
//        glBufferData(GL_ARRAY_BUFFER, out_vertices_arr_len * sizeof(float), out_vertices, GL_STATIC_DRAW);
//    } else {
//        cout << "use vertices. " << endl;
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    }
////    创建索引缓冲对象，并进行绑定，复制索引到索引缓冲中，供opengl使用
//    glGenBuffers(1, &EBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
////    设置顶点属性指针，告知opengl该如何解析这些数据，并启用顶点属性
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
//    glEnableVertexAttribArray(0);
////    color
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
////    texture
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
////    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
////    glEnableVertexAttribArray(0);
////    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
////    glEnableVertexAttribArray(1);
//    
//    setTexture();
////    note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
////    但是EBO是不能解绑的，在VAO解绑定之前。因为glVertexAttribPointer只是将顶点的信息放入了VAO之中，而索引的信息是没有放入的，还是需要从GL_ELEMENT_ARRAY_BUFFER中取。
//    glBindVertexArray(0);
//}
//
//void Parallelogram::recycleResource() {
////    函数VAO、VBO、EBO;
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
////    删除shader program
//    BasicGraph::recycleResource();
//}
//
//int Parallelogram::draw(float out_vertices[], int out_vertices_arr_len) {
////    初始化glfw
//    if(!createWindow()) {
//        return -1;
//    }
////    配置glad
//    if(setGLAD() == -1) {
//        return -1;
//    }
//    glEnable(GL_DEPTH_TEST);
////    vertex shader
//    if(!setVertexShader()) {
//        return -1;
//    }
////    fragment shader
//    if(!setFragmentShader()) {
//        return -1;
//    }
////    shader program
//    if(!setShaderProgram()) {
//        cout << "file::Parallelogram::ERROR::function_setShaderProgram" << endl;
//        return -1;
//    }
//    prepareDataBuffer(out_vertices, out_vertices_arr_len);
////    设置线框模式 Wireframe mode
////    para_1 : 绘制的位置
////    para_2 : 绘制方式
////    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    float last_time = 0.0f;
//    while (!glfwWindowShouldClose(window_)) {
////        处理输入
////        processIuput(window_, last_time);
//        
////        渲染指令
////        绘图之前设置背景颜色
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        
////        绑定纹理单元
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//        
////        设定使用我们的程序进行渲染
//        glUseProgram(shaderProgram);
//        
////        transformation graph
////        glm::mat4 trans_matrix = setTransformation();
//        
////        para_1 : uniform 变量的位置
////        para_2 : 矩阵数量
////        para_3 : 是否转置(Transpose) : OpenGL和GLM均使用列主序(Column-major Ordering)布局，所以不需要转置
////        para_4 : 矩阵数据， GLM并不是把它们的矩阵储存为OpenGL所希望接受的那种，因此我们要先用GLM的自带的函数value_ptr来变换这些数据。
////        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(trans_matrix));
////        mvp transformation
//        glm::mat4 model_matrix = setModelMatrix();
//        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model_matrix));
//        glm::mat4 view_matrix = setViewMatrix();
//        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view_matrix));
//        glm::mat4 projection_matrix = setProjectionMatrix();
//        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection_matrix));
////        在绑定VAO时，绑定的最后一个元素缓冲区对象存储为VAO的元素缓冲区对象。然后，绑定到VAO也会自动绑定该EBO。
//        glBindVertexArray(VAO);
////        para_1 : 绘制的模式
////        para_2 : 绘制顶点的个数，这里填6
////        para_3 : 索引的类型，这里是GL_UNSIGNED_INT
////        para_4 : 指定EBO中的偏移量（或者传递一个索引数组，但是这是当你不在使用索引缓冲对象的时候）
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        
////        交换缓冲区
//        glfwSwapBuffers(window_);
////        查询事件并处理 ： 包括键盘和鼠标的移动等
//        glfwPollEvents();
//    }
//    recycleResource();
////    glDeleteVertexArrays(1, &VAO);
////    glDeleteBuffers(1, &VBO);
////    glDeleteShader(shaderProgram)
//    glfwTerminate();
//    return 0;
//}
