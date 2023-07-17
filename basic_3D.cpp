//
//  basic_3D.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/17.
//

#include "basic_3D.hpp"
// 在使用的位置加入stb_image.h
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

Basic3D :: Basic3D(string out_vertex_shader_source, string out_fragment_shader_source, int width, int height, const char * window_name) {
    Parallelogram(out_vertex_shader_source, out_fragment_shader_source, width, height, window_name);
//    my error3 ： 这里需要再设置vertex_shader_source和fragment_shader_source，不然基类的不会改变。
    if(out_vertex_shader_source != "") {
        vertex_shader_source = out_vertex_shader_source;
    }
    if(out_fragment_shader_source != "") {
        fragment_shader_source = out_fragment_shader_source;
    }
}

bool Basic3D :: setShaderProgram() {
    return Parallelogram::setVertexShader() && Parallelogram::setFragmentShader() && Parallelogram::setShaderProgram();
}

void Basic3D::setTexture() {
//    暂时使用class Parallelogram的纹理设置
    Parallelogram::setTexture();
//    glGenTextures(1, &texture1);
////    激活纹理单元0
////    glActiveTexture(GL_TEXTURE0);
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
////    glActiveTexture(GL_TEXTURE1);
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
}

void Basic3D::prepareDataBuffer(float out_vertices[], int out_vertices_arr_len) {
//    默认的顶点数据和索引
    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
//     为缓冲区传入数据。如果外部传入顶点数据，则使用外部的数据
//    if(out_vertices_arr_len > 1) {
//        cout << "use out_vertices. " << "sizeof(float) * out_vertices_arr_len " << sizeof(float) * out_vertices_arr_len <<endl;
////        my error sizeof(out_vertices) : 为sizeof传入数组首地址和指针均不会评估整个数组的长度
//        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * out_vertices_arr_len, out_vertices, GL_STATIC_DRAW);
//    } else {
//        cout << "use vertices. " << endl;
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    }
    
//    设置顶点属性指针，告知opengl该如何解析这些数据，并启用顶点属性
//    vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
//    set texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
//  设置纹理
    setTexture();
    
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
}

glm::mat4 Basic3D::setModelMatrix(glm::vec3 cube_position) {
    glm::mat4 model;
    model = glm::translate(model, cube_position);
    return model;
}

void Basic3D::setMVP() {
//    将mvp变换集中到一起
//    model matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() , glm::vec3(0.5f, 1.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//    view matrix
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
//    projection matrix
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective( glm::radians(45.0f), getWidth() / getHeight(), 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

int Basic3D :: draw(float out_vertices[], int out_vertices_arr_len) {
//    initglfw and create window
    if(!createWindow()) {
        cout << "Location :: File(basci.cpp), Function(draw);  Error :: createWindow() error!" << endl;
        return -1;
    }
//    glad confirgulation
    if(setGLAD() == -1) {
        cout << "Location :: File(basci.cpp), Function(draw);  Error :: setGLAD() error!" << endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
//    shader program
    if(!setShaderProgram()) {
        cout << "Location :: File(basci.cpp), Function(draw);  Error :: setShaderProgram() error!" << endl;
        return -1;
    }
//    set VAO/VBO, texture
    prepareDataBuffer(out_vertices, out_vertices_arr_len);

//    定义每个立方体的位置
    glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3( 2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f),
      glm::vec3( 1.5f,  2.0f, -2.5f),
      glm::vec3( 1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
//    render loop
    while (!glfwWindowShouldClose(window_)) {
//        process input
        processIuput(window_);
        
//        渲染指令
//        清空屏幕
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
//        绑定纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
//        使用程序
        glUseProgram(shaderProgram);
//        绘制图案
        glBindVertexArray(VAO);
        
//        mvp transformation
        setMVP();
                
//        绘制10个转动的立方体
        for(unsigned int  i = 0; i < 10; ++i) {
            //            微调model matrix
            glm::mat4 model = setModelMatrix(cubePositions[i]);
            float angle = 20.f * (i + 1);
            model = glm::rotate(model, angle * (float)glfwGetTime() * 0.03f, glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
            //        para_1 : 从数据缓冲中哪一个开始绘制，一般从第0个开始
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
//        交换缓冲区
        glfwSwapBuffers(window_);
//        处理事件
        glfwPollEvents();
    }
//    recycleResource();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
//    glDeleteShader(shaderProgram);
    
    glfwTerminate();
    return 0;
}




