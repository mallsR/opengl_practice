//
//  model_load.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/31.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "camera.hpp"
#include "manage.hpp"
#include "3.model_loading/model.hpp"

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
    string WORK_DIR = "/Users/xiaor/Project/xCode/opengl_test/opengl_test/3.model_loading/";
    string scene_vs = "1.model_loading.vs";
    string scene_fs = "1.model_loading.fs";
    string scene_vs_path = WORK_DIR + scene_vs;
    string scene_fs_path = WORK_DIR + scene_fs;
    Shader lighting_shader(scene_vs_path.c_str(), scene_fs_path.c_str());

//    prepare data buffer
//    -------------------
//    Lighting:Lighting maps vertexs

//    light pos
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

//    load model
//    ---------------------------------------
    Model our_model("../source/nanosuit.obj");

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

        lighting_shader.use();

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
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));  // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));    // it's a bit too big for our scene, so scale it down
        lighting_shader.setMat4("model", model);

        our_model.Draw(lighting_shader);

//        交换缓冲区
        glfwSwapBuffers(window_manager.m_window);
//        处理事件
        glfwPollEvents();
    }

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



