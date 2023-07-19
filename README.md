# Projection Description
1. 前期使用basic_graph, draw_triangle, parallelogram, basic_3D.hpp/cpp完成基础部分的练习。可快速渲染不同的物体。
2. 后期构建class Manage，class Shader，class Camera，组合使用更具灵活性，更容易实现复杂的功能。
3. 但两部分代码在引入glad，glm时有重复引入的现象，故不使用时应把basic_graph, draw_triangle, parallelogram, basic_3D.hpp/cpp内容注释。

# Function
1. class Manager : create window, configure glad, manage resource.
2. class Shader : read shader code, create shader program, set uniform.
3. class Camera : create camera coordinate, create view matrix, deal with keyboard/mouse/scroll input.

#  Derived relation
1. BasicGraph -> Triangle
2. BasicGraph -> Parallelogram -> Basic3D
3. Shader
4. Manager

# File and content
1. basic_graph.hpp/cpp : class BasicGraph
2. draw_triangle.hpp/cpp : class Triangle
3. parallelogram.hpp/cpp : class Parallelogram
4. shader.hpp/cpp : class Shader
5. basic_3D.hpp/cpp : class Basic3D
6. manage.hpp/cpp : class Manager 


