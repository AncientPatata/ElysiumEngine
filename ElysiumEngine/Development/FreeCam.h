#pragma once
#include <iostream>
#include <unordered_map>
#include "../vendor/glm/glm.hpp"
#include "../vendor/glad/glad.h"
#include "../vendor/GLFW/glfw3.h"



namespace Development {

    class FirstPersonCamera
    {
    public:
        FirstPersonCamera(const glm::vec3& position, float yaw, float pitch, float fov, float aspectRatio, float nearPlane, float farPlane);
        void ProcessKeyboardInput(float deltaTime);
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        glm::mat4 GetViewMatrix() const;
        glm::mat4 GetProjectionMatrix() const;
        void UpdateCameraVectors();

    private:
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;
        float m_yaw;
        float m_pitch;
        float m_fov;
        float m_aspectRatio;
        float m_nearPlane;
        float m_farPlane;
        float m_movementSpeed;
        float m_mouseSensitivity;
        bool m_firstMouse;
        double m_lastX;
        double m_lastY;

    };

}