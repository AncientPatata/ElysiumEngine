#include "FreeCam.h"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../Core/Input.h"

using namespace Development;

FirstPersonCamera::FirstPersonCamera(const glm::vec3& position, float yaw, float pitch, float fov, float aspectRatio, float nearPlane, float farPlane)
    : m_position(position), m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), m_yaw(yaw), m_pitch(pitch),
    m_fov(fov), m_aspectRatio(aspectRatio), m_nearPlane(nearPlane), m_farPlane(farPlane),
    m_movementSpeed(2.5f), m_mouseSensitivity(0.1f), m_firstMouse(true), m_lastX(0.0), m_lastY(0.0),
    Graphics::Camera(position, fov, aspectRatio, nearPlane, farPlane)
{
    UpdateCameraVectors();
}

void FirstPersonCamera::ProcessKeyboardInput(float deltaTime)
{

    // Process keyboard input to move the camera
    if (Core::Input::IsKeyPressed(GLFW_KEY_W))
        m_position += m_front * m_movementSpeed * deltaTime;
    if (Core::Input::IsKeyPressed(GLFW_KEY_S))
        m_position -= m_front * m_movementSpeed * deltaTime;
    if (Core::Input::IsKeyPressed(GLFW_KEY_A))
        m_position -= m_right * m_movementSpeed * deltaTime;
    if (Core::Input::IsKeyPressed(GLFW_KEY_D))
        m_position += m_right * m_movementSpeed * deltaTime;
    if (Core::Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
        m_position += m_up * m_movementSpeed * deltaTime;
    if (Core::Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
        m_position -= m_up * m_movementSpeed * deltaTime;
}

void FirstPersonCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // Clamp the pitch to avoid flipping the camera
    if (constrainPitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    // Update the camera's front vector
    UpdateCameraVectors();
}

void FirstPersonCamera::UpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

glm::mat4 FirstPersonCamera::GetViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 FirstPersonCamera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}
