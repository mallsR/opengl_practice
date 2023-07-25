// 5. light casters vs


#version 330 core
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    // 变换到世界空间坐标
    FragPos = vec3(model * vec4(aPos, 1.0));
    // 由于fragment shader的计算都是在世界空间坐标中进行的，所以需要将Normal也转换到世界空间坐标。
    // 但由于Normal的特殊性，不能直接使用model matrix进行变换，一个合适的方式是为其设置Normal matrix
    // 计算过程见 ： http://www.lighthouse3d.com/tutorials/glsl-tutorial/the-normal-matrix/
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
}


