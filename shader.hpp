//
//  shader.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/14.
//

#ifndef shader_hpp
#define shader_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include "glm-0.9.8.5/glm/glm.hpp"

using namespace std;

class Shader{
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
    void setVec3(const string & name, float x, float y, float z);
    void setVec3(const string & name, const glm::vec3 & value);
    void setMat4(const string & name, const glm::mat4 & mat);
//    void draw();
private:
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif /* shader_hpp */
