// Texture.h
#pragma once
#include <string>
#include "../vendor/glad/glad.h"

namespace Graphics {

    class Texture
    {
    public:
        Texture(const std::string& imagePath);
        ~Texture();

        void Bind() const;

    private:
        GLuint m_textureID;
    };

}