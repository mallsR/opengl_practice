//
//  camera.hpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/18.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include <glad/glad.h>

// 使用GLM
#include "glm-0.9.8.5/glm/glm.hpp"
#include "glm-0.9.8.5/glm/gtc/matrix_transform.hpp"
#include "glm-0.9.8.5/glm/gtc/type_ptr.hpp"

// camera move direction
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera{
public:
//    camera attributes
    glm::vec3 camera_pos;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
    glm::vec3 camera_right;
    glm::vec3 world_up;
    // euler Angles
    float pitch;
    float yaw;
//    camera options
    float movement_speed;
    float mouse_sensitivity;
    float zoom;
    
//    constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float out_pitch = PITCH, float out_yaw = YAW);
//    constructor with scalar values
    Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float out_pitch = PITCH, float out_yaw = YAW);
//    compute view matrix using euler angles
    glm::mat4 getViewMatrix();
//    process keyboard input, change camera_pos
    void processKeyboard(Camera_Movement direction, float delta_time);
//    process mouse input, change look direction
    void processMouseMovement(float x_offset, float y_offset, GLboolean constrainPitch = true);
//    process mouse scroll
    void processMouseScroll(float y_offset);
private:
    void updateCameraVectors();
};

#endif /* camera_hpp */
