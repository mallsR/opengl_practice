//
//  draw_triangle.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/11.
//

#ifndef draw_triangle_hpp
#define draw_triangle_hpp

#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "basic_graph.hpp"
#include <string>

using namespace std;

class Triangle : public BasicGraph{
private:
    string name;
public:
    int draw();
};

#endif /* draw_triangle_hpp */
