//
//  main.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/10.
//

//#include "basic_graph.hpp"
//#include "parallelogram.hpp"
//#include "basic_3D.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm-0.9.8.5/glm/glm.hpp"
#include "glm-0.9.8.5/glm/gtc/matrix_transform.hpp"
#include "glm-0.9.8.5/glm/gtc/type_ptr.hpp"

#include "shader.hpp"
#include "camera.hpp"
#include "manage.hpp"

// 在使用的位置加入stb_image.h
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// 函数声明区域
//----------------
void framebuffer_size_callback(GLFWwindow * window, int width, int  height);
void mouse_callback(GLFWwindow * window, double out_x_pos, double out_y_pos);
void scroll_callback(GLFWwindow * window, double x_offset, double y_offset);
void processInput(GLFWwindow * window);
unsigned int loadTexture(char const * path);

// settings
//----------------
// 窗口尺寸设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
// 传入初始位置
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float last_x = SCR_WIDTH / 2.0f;
float last_y = SCR_HEIGHT / 2.0f;
bool first_mouse = true;

float delta_time = 0.0f;
float last_time = 0.0f;

// lighting
glm::vec3 light_pos(1.2f, 1.2f, 1.2f);

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
    
//    string out_vertex_shader_source = "#version 330 core\n"
//    "layout (location = 0) in vec3 aPos;\n"
//    "layout (location = 1) in vec2 aTexCoord;\n"
//    "out vec2 TexCoord;\n"
//    "uniform mat4 model;  // model matrix\n"
//    "uniform mat4 view;     // view matrix\n"
//    "uniform mat4 projection;      //projection matrix\n"
//    "void main()\n"
//    "{\n"
//    "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
//    "    // TexCoord = aTexCoord;\n"
//    "    TexCoord = vec2(aTexCoord.x, aTexCoord.y);"
//    "}\n";
//
//    string out_fragment_shader_source = "#version 330 core\n"
//    "out vec4 FragColor;\n"
//    "in vec2 TexCoord;\n"
//    "uniform sampler2D texture1;\n"
//    "uniform sampler2D texture2;\n"
//    "void main()\n"
//    "{\n"
//    "    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);\n"
//    "}\n";
//
//    float vertices[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };
//    Parallelogram * parallelogram = new Parallelogram(out_vertex_shader_source, out_fragment_shader_source);
//    int parallelogram_flag = parallelogram->draw();
//    if (parallelogram_flag) {
//        cout << "FILE::MAIN::ERROR::PARALLELOGRAM::Texture::failed" << endl;
//    }
//    delete parallelogram;
    
//    3D : 绘制立方体
//    Basic3D * basic_3D = new Basic3D(out_vertex_shader_source, out_fragment_shader_source);
//    int basic_3D_flag = basic_3D->draw(vertices, 180);
//    if(basic_3D_flag) {
//        cout << "Location :: File(main.cpp); ERROR :: basic_3D->draw()" << endl;
//    }
//    delete basic_3D;
    
    
//    lighting :: create scene
//    string out_vertex_shader_source = "#version 330 core\n"
//                                    "layout (location = 0) in vec3 aPos;\n"
//                                    "uniform mat4 model;\n"
//                                    "uniform mat4 view;\n"
//                                    "uniform mat4 projection;\n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
//                                    "}\n";
//    string out_fragment_shader_source = "#version 330 core\n"
//                                    "out vec4 FragColor;\n"
//                                    "uniform vec3 objectColor;  //物体可以反射的颜色 \n"
//                                    "uniform vec3 lightColor;\n"
//                                    "void main()\n"
//                                    "{\n"
//                                    "   FragColor = vec4(lightColor * objectColor, 1.0);\n"
//                                    "}\n";
//    Basic3D * scene = new Basic3D(out_vertex_shader_source, out_fragment_shader_source);
//    scene->createScene();
//    delete scene;
    
    
    Manage window_manager;
//    创建窗口
//    ------------------
    window_manager.createWindow();
//    为glfw配置系列回调函数
//    ------------------
//    设置窗口大小
    glfwSetWindowSizeCallback(window_manager.m_window, framebuffer_size_callback);
//    设置鼠标移动
    glfwSetCursorPosCallback(window_manager.m_window, mouse_callback);
//    设置滚轮回调函数
    glfwSetScrollCallback(window_manager.m_window, scroll_callback);
    
// tell GLFW to capture our mouse
    glfwSetInputMode(window_manager.m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
//    glad configurate
    window_manager.setGLAD();
    
// configure global opengl state
// -----------------------------
    glEnable(GL_DEPTH_TEST);
    
//    shadaer program
//    ------------------------------
//    着色器程序 ：用于为场景中的物体着色
//    加载的文件路径，不用带后缀
    Shader lighting_shader("/Users/xiaor/Project/xCode/opengl_test/opengl_test/lighting/4.1.colors_vs", "/Users/xiaor/Project/xCode/opengl_test/opengl_test/lighting/4.1.colors_fs");
//    着色器程序 ： 用于为光源着色
    Shader light_cube_shader("/Users/xiaor/Project/xCode/opengl_test/opengl_test/lighting/light_cube_vs", "/Users/xiaor/Project/xCode/opengl_test/opengl_test/lighting/light_cube_fs");
    
//    prepare data buffer
//    -------------------
//    float vertices[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//    };
    
//    Lighting:Lighting maps vertexs
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
    
//    为场景中物体加载顶点
    unsigned int lighting_VAO, VBO;
    glGenVertexArrays(1, &lighting_VAO);
    glGenBuffers(1, &VBO);
    
//    为顶点缓冲对象绑定缓冲区，并传入数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(lighting_VAO);
    
//    设置顶点属性指针
//    pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
//    normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
//    lighting maps
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
//    为光源加载顶点
    unsigned int light_cube_VAO;
    glGenVertexArrays(1, & light_cube_VAO);
    glBindVertexArray(light_cube_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
//    set lighting maps
    string WORK_DIR = "/Users/xiaor/Project/xCode/opengl_test/opengl_test/lighting/";
    string diffuse_map_picture = "container2.png";
    string diffuse_map_path = WORK_DIR + diffuse_map_picture;
    cout << "diffuse_map_path : " << diffuse_map_path << endl;
    string specular_map_picture = "container2_specular.png";
    string specular_map_path = WORK_DIR + specular_map_picture;
    cout << "specular_map_path : " << specular_map_path << endl;
    unsigned int diffuse_map = loadTexture(diffuse_map_path.c_str());
    unsigned int specular_map = loadTexture(specular_map_path.c_str());
    
//    绑定箱子的不同纹理到纹理单元
    lighting_shader.use();
    lighting_shader.setInt("material.diffuse", 0);
    lighting_shader.setInt("material.specular", 1);
    
//    render loop
//    ---------------------
    while (!glfwWindowShouldClose(window_manager.m_window)) {
        float current_time = static_cast<float>(glfwGetTime());
        delta_time = current_time - last_time;
        last_time = current_time;
        
//        处理输入
        processInput(window_manager.m_window);
//        清空颜色
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
//        设置场景shader uniform
//        设置phong lighting model需要的光源和摄影机位置等信息
        lighting_shader.use();
//        lighting_shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
//        lighting_shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lighting_shader.setVec3("light.position", light_pos);
        lighting_shader.setVec3("viewPos", camera.camera_pos);
//        设置材质
//        lighting_shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//        lighting_shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        lighting_shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        lighting_shader.setFloat("material.shininess", 64.0f);
//        设置基础光照
        lighting_shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
        lighting_shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
        lighting_shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//        光源的颜色随时间改变
//        glm::vec3 light_color;
//        light_color.x = sin(glfwGetTime() * 2.0f);
//        light_color.y = sin(glfwGetTime() * 0.7f);
//        light_color.z = sin(glfwGetTime() * 1.3f);
//        glm::vec3 diffuse_color = light_color * glm::vec3(0.5f);
//        glm::vec3 ambient_color = light_color * glm::vec3(0.2f);
//        lighting_shader.setVec3("light.ambient", ambient_color);
//        lighting_shader.setVec3("light.diffuse", diffuse_color);
        
//        设置mvp变换
//        -----------------------
//        set model matrix : 放在原位置
        glm::mat4 model = glm::mat4(1.0f);
        lighting_shader.setMat4("model", model);
        
//        set view matrix
        glm::mat4 view = camera.getViewMatrix();
        lighting_shader.setMat4("view", view);
//        set projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.f);
        lighting_shader.setMat4("projection", projection);
        
        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse_map);
//        bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_map);
        
//        绘制场景中的物体
        glBindVertexArray(lighting_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
//        绘制灯
        light_cube_shader.use();
//        设置mvp变换
//        ----------------
        model = glm::mat4(1.0f);
        model = glm::translate(model, light_pos);
        model = glm::scale(model, glm::vec3(0.2f));
        light_cube_shader.setMat4("model", model);
        light_cube_shader.setMat4("view", view);
        light_cube_shader.setMat4("projection", projection);
        
        glBindVertexArray(light_cube_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
//        交换缓冲区
        glfwSwapBuffers(window_manager.m_window);
//        处理事件
        glfwPollEvents();
    }
//    回收所有资源
//    --------------------------
    glDeleteVertexArrays(1, &lighting_VAO);
    glDeleteVertexArrays(1, &light_cube_VAO);
    glDeleteBuffers(1, &VBO);
    
//   关闭窗口
    glfwTerminate();
    return 0;
}

// 函数具体实现区域
// -------------------
// 设置视口大小
void framebuffer_size_callback(GLFWwindow * window, int width, int  height) {
//    通过调用glViewport函数，设置窗口维度
//    para_0, para_1，设置窗口左下角的位置，para_2,para_3设置窗口宽高
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window) {
//    按下ESC，关闭窗口
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboard(FORWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyboard(BACKWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyboard(LEFT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyboard(RIGHT, delta_time);
    }
}

void mouse_callback(GLFWwindow * window, double out_x_pos, double out_y_pos) {
    float x_pos = static_cast<float>(out_x_pos);
    float y_pos = static_cast<float>(out_y_pos);
    
    if (first_mouse) {
        last_x = x_pos;
        last_y = y_pos;
        first_mouse = false;
    }
    
//    compute offset
    double x_offset = x_pos - last_x;
    double y_offset = last_y - y_pos;
    
//    更新last_pos
    last_x = x_pos;
    last_y = y_pos;
    
//    利用偏移量计算pitch and yaw，更新摄影机的向量
    camera.processMouseMovement(x_offset, y_offset);
}


void scroll_callback(GLFWwindow * window, double x_offset, double y_offset) {
    camera.processMouseScroll(static_cast<float>(y_offset));
}


unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
        cout << "load texture successfully." << endl;
    }
    else
    {
        std::cout << "Location::File(main.cpp),Function(loadTexture); " << endl <<
        "ERROR::Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

