#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Math {

    class Transform {
    public:
        Transform(const glm::vec3& position = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f))
            : m_position(position), m_rotation(rotation), m_scale(scale) {}

        glm::mat4 GetMatrix() const {
            glm::mat4 matrix = glm::mat4(1.0f);
            matrix = glm::translate(matrix, m_position);
            matrix = matrix * glm::toMat4(glm::quat(m_rotation));
            matrix = glm::scale(matrix, m_scale);
            return matrix;
        }

        void SetPosition(const glm::vec3& position) {
            m_position = position;
        }

        void SetRotation(const glm::vec3& rotation) {
            m_rotation = rotation;
        }

        void SetScale(const glm::vec3& scale) {
            m_scale = scale;
        }

        glm::vec3 GetPosition() const {
            return m_position;
        }

        glm::vec3 GetRotation() const {
            return m_rotation;
        }

        glm::vec3 GetScale() const {
            return m_scale;
        }

    private:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;
    };

}