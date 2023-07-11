//
//  main.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/10.
//

#include <iostream>
#include "basic_graph.hpp"
#include "draw_triangle.hpp"

using namespace std;

int main() {
//    定义三角形类
    Triangle triangle;
    int flag = triangle.draw();
    if(flag) {
        cout << "ERROR::Triangle::draw" << endl;
    }
    return 0;
}

