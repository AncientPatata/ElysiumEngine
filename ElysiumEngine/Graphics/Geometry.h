// Geometry.h
#pragma once
#include <vector>
#include <string>
#include "../vendor/glm/glm.hpp"
#include "../vendor/glad/glad.h"

namespace Graphics {

    struct Vertex
    {
        Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoords)
			: position(position), normal(normal), texCoords(texCoords) {}
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    class Geometry
    {
    public:
        Geometry(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        ~Geometry();

        void Draw() const;
        static Geometry* LoadObj(const std::string& path);

    private:
        GLuint m_VAO, m_VBO, m_EBO;
        std::vector<unsigned int> m_indices;
    };
}