// Shader.h
#pragma once
#include <string>
#include "../vendor/glad/glad.h"
#include "../vendor/glm/glm.hpp"

#include "../Core/ResourceManager/Resource.h"

namespace Graphics {

    class Shader : public Core::Resource
    {
    public:
        Shader(const std::string& shaderAssetFilepath, const std::string& vertexSource, const std::string& fragmentSource);

        ~Shader();

        void Use() const;

        GLuint GetUniformLocation(const std::string& name) const;
        void SetUniform(const std::string& name, float value) const;
        void SetUniform(const std::string& name, const glm::mat4& matrix) const;
        void SetUniform(const std::string& name, const glm::vec3& value) const;


        static std::string GetResourceType() {
            return "Shader";
        }

    private:
        bool CompileShader(const std::string& source, GLuint id) const;
        GLuint m_programID;
    };

}