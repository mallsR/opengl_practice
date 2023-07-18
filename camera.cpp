//
//  camera.cpp
//  opengl_test
//
//  Created by xiaoR on 2023/7/18.
//

#include "camera.hpp"

//  提供前向向量默认值，
Camera::Camera(glm::vec3 positon, glm::vec3 up, float out_pitch, float out_yaw):camera_front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM) {
    camera_pos = positon;
    world_up = up;
    pitch = out_pitch;
    yaw = out_yaw;
    updateCameraVectors();
}

Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float out_pitch, float out_yaw) :camera_front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM) {
    camera_pos = glm::vec3(pos_x, pos_y, pos_z);
    world_up = glm::vec3(up_x, up_y, up_z);
    pitch = out_pitch;
    yaw = out_yaw;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
}

void Camera::processKeyboard(Camera_Movement direction, float delta_time) {
    float velocity = movement_speed * delta_time;
    if (direction == FORWARD) {
        camera_pos += camera_front * velocity;
    }
    if (direction == BACKWARD) {
        camera_pos -= camera_front * velocity;
    }
    if (direction == LEFT) {
        camera_pos -= camera_right * velocity;
    }
    if (direction == RIGHT) {
        camera_pos += camera_right * velocity;
    }
}

void Camera::processMouseMovement(float x_offset, float y_offset, GLboolean constrainPitch) {
    x_offset *= mouse_sensitivity;
    y_offset *= mouse_sensitivity;
    
    pitch += y_offset;
    yaw += x_offset;
    
    if (constrainPitch) {
        if (pitch >= 90.0f) {
            pitch = 89.0f;
        }
        if (pitch <= 90.0f) {
            pitch = -89.0f;
        }
    }
    
//    更新摄影机信息
    updateCameraVectors();
}

void Camera::processMouseScroll(float y_offset) {
    zoom -= (float)y_offset;
    if (zoom < 1.0f) {
        zoom = 1.0f;
    }
    if (zoom > 45.0f) {
        zoom = 45.0f;
    }
}

void Camera::updateCameraVectors() {
//    计算相机前向向量
    camera_front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    camera_front.y = sin(glm::radians(pitch));
    camera_front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    camera_front = glm::normalize(camera_front);
//    相机右向向量和向上向量
    camera_right = glm::normalize(glm::cross(camera_front, world_up));
    camera_up = glm::normalize(glm::cross(camera_right, camera_front));
}
