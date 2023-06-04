#include "Renderer3D.h"


using namespace Renderer;

Renderer3D::Renderer3D(Graphics::Camera* camera)
    : m_camera(camera)
{
}

Renderer3D::~Renderer3D()
{
}

void Renderer3D::Render(const std::vector<Renderer::StaticMesh*>& meshes)
{
    // Set up view and projection matrices from the camera
    glm::mat4 view = m_camera->GetViewMatrix();
    glm::mat4 projection = m_camera->GetProjectionMatrix();

    for (Renderer::StaticMesh* mesh : meshes) {
        // Set the mesh's transformation matrix
        glm::mat4 model = mesh->GetTransform()->GetMatrix();

        // Use the material's shader and set the uniform matrices
        mesh->GetMaterial()->Use();
        mesh->GetMaterial()->GetShader()->SetUniform("model", model);
        mesh->GetMaterial()->GetShader()->SetUniform("view", view);
        mesh->GetMaterial()->GetShader()->SetUniform("projection", projection);

        // Draw the mesh
        mesh->Draw();
    }
}
