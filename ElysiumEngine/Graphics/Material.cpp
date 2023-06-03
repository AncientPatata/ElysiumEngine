// Material.cpp
#include "Material.h"
#include "../Core/Utils.h"
#include "nlohmann/json.hpp"
#include "../Core/Log.h"

#include "../Core/ResourceManager/ResourceManager.h"

using namespace Graphics;

Material::Material(const std::string& materialAssetFilepath)
    : Core::Resource(materialAssetFilepath)
{
}

Material::~Material()
{
}

void Material::Use() const
{
    if (m_shader)
    {
        m_shader->Use();
        for (const auto& texture : m_textures)
        {
            texture.second.Bind();
        }
    }
}

bool Material::SetFloatParameter(const std::string& name, float value)
{
    auto it = m_floatParameters.find(name);
    if (it != m_floatParameters.end())
    {
        it->second = value;
        return true;
    }
    return false;
}

bool Material::SetVec3Parameter(const std::string& name, const glm::vec3& value)
{
    auto it = m_vec3Parameters.find(name);
    if (it != m_vec3Parameters.end())
    {
        it->second = value;
        return true;
    }
    return false;
}

const Texture* Material::GetTexture(const std::string& name) const
{
    auto it = m_textures.find(name);
    if (it != m_textures.end())
    {
        return &(it->second);
    }
    return nullptr;
}


void Material::LoadShader(const std::string& shaderAssetFilepath)
{
    try {
        m_shader = std::make_unique<Graphics::Shader>(*Core::ResourceManager::Instance().Load<Graphics::Shader>(shaderAssetFilepath));
    }
    catch (std::exception& e)
    {
        Core::Log::Instance().Out(Core::LogLevel::Error) << "Failed to load shader for material from asset file: " << shaderAssetFilepath << '\n' << "details : \n" << e.what() << "\n";

    }
}

void Material::LoadTextures(const std::string& texturesAssetFilepath)
{
    try
    {
        nlohmann::json data = nlohmann::json::parse(Core::ReadFile(texturesAssetFilepath));

        for (const auto& textureData : data)
        {
            std::string name = textureData["Name"].get<std::string>();
            std::string path = textureData["Path"].get<std::string>();

            Texture texture(path);
            if (true)
            {
                m_textures.emplace(name, texture);
            }
            else
            {
                Core::Log::Instance().Out(Core::LogLevel::Error) << "Failed to load texture for material from asset file: " << path << '\n';
            }
        }
    }
    catch (nlohmann::json::exception& e)
    {
        Core::Log::Instance().Out(Core::LogLevel::Error) << "Failed to parse textures asset file: " << e.what() << '\n';
    }
}

void Material::LoadShaderParameters(const std::string& shaderParametersAssetFilepath)
{
    try
    {
        nlohmann::json data = nlohmann::json::parse(Core::ReadFile(shaderParametersAssetFilepath));

        if (data.contains("FloatParameters"))
        {
            const nlohmann::json& floatParameters = data["FloatParameters"];
            for (const auto& parameter : floatParameters.items())
            {
                std::string name = parameter.key();
                float value = parameter.value().get<float>();
                m_floatParameters.emplace(name, value);
            }
        }

        if (data.contains("Vec3Parameters"))
        {
            const nlohmann::json& vec3Parameters = data["Vec3Parameters"];
            for (const auto& parameter : vec3Parameters.items())
            {
                std::vector<float> values = parameter.value().get<std::vector<float>>();
                std::string name = parameter.key();
                glm::vec3 value = glm::vec3(values[0], values[1], values[2]);
                m_vec3Parameters.emplace(name, value);
            }
        }
    }
    catch (nlohmann::json::exception& e)
    {
        Core::Log::Instance().Out(Core::LogLevel::Error) << "Failed to parse shader parameters asset file: " << e.what() << '\n';
    }
}