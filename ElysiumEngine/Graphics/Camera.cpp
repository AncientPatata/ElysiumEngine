// Camera.cpp
#include "Camera.h"

using namespace Graphics;

Camera::Camera(const glm::vec3& position, float fov, float aspectRatio, float nearPlane, float farPlane)
    : m_position(position), m_up(glm::vec3(0.0f, 1.0f, 0.0f)), m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_fov(fov), m_aspectRatio(aspectRatio), m_nearPlane(nearPlane), m_farPlane(farPlane)
{
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
}