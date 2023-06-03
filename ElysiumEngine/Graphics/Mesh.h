// Mesh.h
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

    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();

        void Draw(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) const;
        static Mesh* LoadObj(const std::string& path);

    private:
        GLuint m_VAO, m_VBO, m_EBO;
        std::vector<unsigned int> m_indices;
    };
}