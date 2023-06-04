#pragma once
#include "../Core/ResourceManager/Resource.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Shader.h"
#include "nlohmann/json.hpp"
#include <unordered_map>
#include <memory>



namespace Graphics {

    class Material : public Core::Resource {
    public:
        Material(const std::string& materialAssetFilepath);
        ~Material();

        void Use() const;

        bool SetFloatParameter(const std::string& name, float value);
        bool SetVec3Parameter(const std::string& name, const glm::vec3& value);

        const Texture* GetTexture(const std::string& name) const;

        void LoadShader(const std::string& shaderAssetFilepath);
        void LoadTextures(nlohmann::json data);
        void LoadShaderParameters(nlohmann::json data);

        const Shader* GetShader() const {
            return m_shader;
		}

        static std::string GetResourceType() {
			return "Material";
		}
    private:

        std::unordered_map<std::string, Texture> m_textures;
        Shader* m_shader;
        std::unordered_map<std::string, float> m_floatParameters;
        std::unordered_map<std::string, glm::vec3> m_vec3Parameters;
    };

}