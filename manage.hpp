//
//  manage.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/19.
//

#ifndef manage_hpp
#define manage_hpp

#include <stdio.h>
#include <iostream>
// 引入glad 和 glfw头文件
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

class Manage{
public:
//    members
    GLFWwindow * m_window;
    int m_width;
    int m_height;
    const char * m_window_name;
//    functions
    Manage(int width = 800, int height = 600, const char * window_name = "new_window");
    bool createWindow();
    bool setGLAD();
    
};

#endif /* manage_hpp */
