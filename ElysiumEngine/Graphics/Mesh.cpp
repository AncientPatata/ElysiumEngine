// Mesh.cpp
#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace Graphics;


Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices): m_indices(indices)
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Mesh::Draw(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) const
{
    // Calculate the transformation matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, scale);

    // Set the model matrix in the shader program (assuming you have a shader program)
    // shaderProgram.SetUniformMatrix4fv("model", modelMatrix);

    // Render the mesh
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
Mesh* Mesh::LoadObj(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        // Error handling for failed file loading
        // You can print an error message or throw an exception
        return nullptr;
    }

    // Process the mesh data from the scene
    aiMesh* mesh = scene->mMeshes[0]; // Assuming there's only one mesh in the OBJ file

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Process vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        aiVector3D position = mesh->mVertices[i];
        aiVector3D normal;
        if (mesh->HasNormals()) {
            normal = mesh->mNormals[i];
        }        
        aiVector3D texCoords;
        if (mesh->HasTextureCoords(0)) {
            texCoords = mesh->mTextureCoords[0][i];

        }

        vertices.emplace_back(Vertex(
            glm::vec3(position.x, position.y, position.z),
            glm::vec3(normal.x, normal.y, normal.z),
            glm::vec2(texCoords.x, texCoords.y)
        ));
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Create and return the mesh
    return new Mesh(vertices, indices);
}
