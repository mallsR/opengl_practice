//
//  manage.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/19.
//

#include "manage.hpp"

Manage::Manage(int width, int height, const char * window_name) {
    m_width = width;
    m_height = height;
    m_window_name = window_name;
}

bool Manage::createWindow() {
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
//    ------------------
    m_window = glfwCreateWindow(m_width, m_height, m_window_name, NULL, NULL);
    if (m_window == NULL) {
        cout << "Location :: file(manage.cpp), Function(createWindow), ERROR :: createWindow failed." << endl;
        return false;
    }
//    通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(m_window);
    return true;
}

bool Manage::setGLAD() {
//    设置glad，管理opengl函数的指针
//    ------
//    给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout<<"Location :: File(manage.cpp), Function(setGLAD), ERROR :: Failed to initialize GLAD"<<endl;
        return false;
    }
    return true;
}
