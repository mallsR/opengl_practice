//
//  main.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/10.
//

#include "basic_graph.hpp"
#include "draw_triangle.hpp"

int main() {
//    定义基础图形类
//    BasicGraph *  basic_graph_obj = new BasicGraph();
//    int basic_flag = basic_graph_obj->draw();
//    if(basic_flag) {
//        cout << "ERROR::BasicGraph::draw" << endl;
//    }
//    delete basic_graph_obj;
//    定义三角形类
    Triangle * triangle = new Triangle();
    int flag = triangle->draw();
    if(flag) {
        cout << "ERROR::Triangle::draw" << endl;
    }
    delete triangle;
    return 0;
}

