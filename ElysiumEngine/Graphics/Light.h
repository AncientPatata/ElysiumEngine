#pragma once
#include "glm/glm.hpp"

namespace Graphics {
    class Light {
    public:
        glm::vec3 position;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        Light(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
            : position(position), ambient(ambient), diffuse(diffuse), specular(specular) {}
    };
}