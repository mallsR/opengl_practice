//
//  shader.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/14.
//

#ifndef shader_hpp
#define shader_hpp

#include "basic_graph.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Shader : public BasicGraph {
public:
//    程序ID
    unsigned int ID;
    Shader(const char * vertex_path = NULL, const char * fragment_path = NULL);
//    激活着色器
    void use();
//    uniform工具函数
    void setBool(const string & name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void draw();
};

#endif /* shader_hpp */
