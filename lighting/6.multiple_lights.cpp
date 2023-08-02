//
//  main.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/10.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#include "includes/glm-0.9.8.5/glm/glm.hpp"
//#include "includes/glm-0.9.8.5/glm/gtc/matrix_transform.hpp"
//#include "includes/glm-0.9.8.5/glm/gtc/type_ptr.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    string WORK_DIR = "/Users/xiaor/Project/xCode/opengl_test/opengl_test/lighting/";
    string scene_vs = "6.multiple_lights.vs";
    string scene_fs = "6.multiple_lights.fs";
    string scene_vs_path = WORK_DIR + scene_vs;
    string scene_fs_path = WORK_DIR + scene_fs;
    Shader lighting_shader(scene_vs_path.c_str(), scene_fs_path.c_str());
//    着色器程序 ： 用于为光源着色
    string illuminant_vs = "light_cube_vs";
    string illuminant_fs = "light_cube_fs";
    string illuminant_vs_path = WORK_DIR + illuminant_vs;
    string illuminant_fs_path = WORK_DIR + illuminant_fs;
    Shader light_cube_shader(illuminant_vs_path.c_str(), illuminant_fs_path.c_str());
    
//    prepare data buffer
//    -------------------
//    Lighting:Lighting maps vertexs
    float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };
//    box pos
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
    
//    light pos
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
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
//         be sure to activate shader when setting uniforms/drawing objects
//        -------------------------------------------------------------------
//        cout << "camera_pos : " << camera.camera_pos.x << ", " << camera.camera_pos.y << ", " << camera.camera_pos.z << endl;
//        cout << "camera_front : " << camera.camera_front.x <<", " << camera.camera_pos.y << ", " << camera.camera_pos.z << endl;
        lighting_shader.use();

//        camera pos and specular shininess
        lighting_shader.setVec3("viewPos", camera.camera_pos);
        lighting_shader.setFloat("material.shininess", 32.0f);
        
//        directional light
//        --------------------------------------------
        // directional light
        lighting_shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lighting_shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        lighting_shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        lighting_shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        lighting_shader.setVec3("pointLights[0].position", pointLightPositions[0]);
        lighting_shader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        lighting_shader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        lighting_shader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lighting_shader.setFloat("pointLights[0].constant", 1.0f);
        lighting_shader.setFloat("pointLights[0].linear", 0.09f);
        lighting_shader.setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        lighting_shader.setVec3("pointLights[1].position", pointLightPositions[1]);
        lighting_shader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        lighting_shader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        lighting_shader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        lighting_shader.setFloat("pointLights[1].constant", 1.0f);
        lighting_shader.setFloat("pointLights[1].linear", 0.09f);
        lighting_shader.setFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        lighting_shader.setVec3("pointLights[2].position", pointLightPositions[2]);
        lighting_shader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        lighting_shader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        lighting_shader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        lighting_shader.setFloat("pointLights[2].constant", 1.0f);
        lighting_shader.setFloat("pointLights[2].linear", 0.09f);
        lighting_shader.setFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        lighting_shader.setVec3("pointLights[3].position", pointLightPositions[3]);
        lighting_shader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        lighting_shader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        lighting_shader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        lighting_shader.setFloat("pointLights[3].constant", 1.0f);
        lighting_shader.setFloat("pointLights[3].linear", 0.09f);
        lighting_shader.setFloat("pointLights[3].quadratic", 0.032f);
        // spotLight
        lighting_shader.setVec3("spotLight.position", camera.camera_pos);
        lighting_shader.setVec3("spotLight.direction", camera.camera_front);
        lighting_shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lighting_shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lighting_shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lighting_shader.setFloat("spotLight.constant", 1.0f);
        lighting_shader.setFloat("spotLight.linear", 0.09f);
        lighting_shader.setFloat("spotLight.quadratic", 0.032f);
        lighting_shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lighting_shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        
        
//        设置材质
//        lighting_shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//        lighting_shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
//        lighting_shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        
//        设置基础光照
//        lighting_shader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
//        lighting_shader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
//        lighting_shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        
//        设置mvp变换
//        -----------------------
//        set view matrix
        glm::mat4 view = camera.getViewMatrix();
        lighting_shader.setMat4("view", view);
//        set projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.f);
        lighting_shader.setMat4("projection", projection);
        
//        set model matrix : 放在原位置
        glm::mat4 model = glm::mat4(1.0f);
        lighting_shader.setMat4("model", model);
        
        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse_map);
//        bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_map);
        
//        绘制场景中的物体
        glBindVertexArray(lighting_VAO);
        for(unsigned int i = 0; i < 10; ++i) {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lighting_shader.setMat4("model", model);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
//        绘制点光源
        light_cube_shader.use();
//        设置mvp变换
//        ----------------
        light_cube_shader.setMat4("view", view);
        light_cube_shader.setMat4("projection", projection);
        
        glBindVertexArray(light_cube_VAO);
        for (unsigned int i = 0; i < 4; ++i) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f));
            light_cube_shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
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
//        cout << " width : " << width << " height : " << height << " nrComponents : " << nrComponents << endl;
    }
    else
    {
        std::cout << "Location::File(main.cpp),Function(loadTexture); " << endl <<
        "ERROR::Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
