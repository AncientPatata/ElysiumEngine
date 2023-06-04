#pragma once

#include "Camera.h"
#include "StaticMesh.h"

namespace Renderer {


    class Renderer3D {
    public:
        Renderer3D(Graphics::Camera* camera);
        ~Renderer3D();

        void Render(const std::vector<Renderer::StaticMesh*>& meshes);

    private:
        Graphics::Camera* m_camera;
    };

}