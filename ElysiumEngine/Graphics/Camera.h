// Camera.h
#pragma once
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

namespace Graphics {

    class Camera
    {
    public:
        Camera(const glm::vec3& position, float fov, float aspectRatio, float nearPlane, float farPlane);

        virtual glm::mat4 GetViewMatrix() const;
        virtual glm::mat4 GetProjectionMatrix() const;

    private:
        glm::vec3 m_position;
        glm::vec3 m_up;
        glm::vec3 m_front;
        float m_fov;
        float m_aspectRatio;
        float m_nearPlane;
        float m_farPlane;
    };

}