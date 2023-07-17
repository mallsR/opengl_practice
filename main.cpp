//
//  main.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/10.
//

//#include "basic_graph.hpp"
#include "parallelogram.hpp"
#include "basic_3D.hpp"

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
//    Shader our_shader("33shader_vs.txt", "33shader_fs.txt");
//    our_shader.draw();
    
//    Texture
//    string out_vertex_shader_source = "#version 330 core\n"
//    "layout (location = 0) in vec3 aPos;\n"
//    "layout (location = 1) in vec3 aColor;\n"
//    "layout (location = 2) in vec2 aTexCoord;\n"
//    "out vec3 ourColor;\n"
//    "out vec2 TexCoord;\n"
//    "uniform mat4 transform; // 旋转图像 \n"
//    "uniform mat4 model;  // model matrix\n"
//    "uniform mat4 view;     // view matrix\n"
//    "uniform mat4 projection;      //projection matrix\n"
//    "void main()\n"
//    "{\n"
//    "    // gl_Position = transform * vec4(aPos, 1.0);\n"
//    "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
//    "    ourColor = aColor;\n"
//    "    TexCoord = aTexCoord;\n"
//    "}\n";
//
//    string out_fragment_shader_source = "#version 330 core\n"
//    "out vec4 FragColor;\n"
//    "in vec3 ourColor;\n"
//    "in vec2 TexCoord;\n"
//    "// uniform sampler2D ourTexture;\n"
//    "uniform sampler2D texture1;\n"
//    "uniform sampler2D texture2;\n"
//    "void main()\n"
//    "{\n"
//    "    // FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);\n"
//    "    // FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);\n"
//    "    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);\n"
//    "    // FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);\n"
//    "}\n";
    
    string out_vertex_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 model;  // model matrix\n"
    "uniform mat4 view;     // view matrix\n"
    "uniform mat4 projection;      //projection matrix\n"
    "void main()\n"
    "{\n"
    "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
    "    // TexCoord = aTexCoord;\n"
    "    TexCoord = vec2(aTexCoord.x, aTexCoord.y);"
    "}\n";

    string out_fragment_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec2 TexCoord;\n"
    "uniform sampler2D texture1;\n"
    "uniform sampler2D texture2;\n"
    "void main()\n"
    "{\n"
    "    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);\n"
    "}\n";
    
    float vertices[] = {
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
//    Parallelogram * parallelogram = new Parallelogram(out_vertex_shader_source, out_fragment_shader_source);
//    int parallelogram_flag = parallelogram->draw();
//    if (parallelogram_flag) {
//        cout << "FILE::MAIN::ERROR::PARALLELOGRAM::Texture::failed" << endl;
//    }
//    delete parallelogram;
    
//    3D : 绘制立方体
    
    Basic3D * basic_3D = new Basic3D(out_vertex_shader_source, out_fragment_shader_source);
    int basic_3D_flag = basic_3D->draw(vertices, 180);
    if(basic_3D_flag) {
        cout << "Location :: File(main.cpp); ERROR :: basic_3D->draw()" << endl;
    }
    delete basic_3D;
    return 0;
}

