// MaterialResourceLoader.cpp
#include "MaterialResourceLoader.h"
#include "../Core/Utils.h"
#include "nlohmann/json.hpp"
#include "../Core/Log.h"
#include <memory>

using namespace Resources;

std::unique_ptr<Core::Resource> MaterialResourceLoader::Load(const std::string& filePath)
{
    std::string resourceFile;
    std::unique_ptr<Graphics::Material> material = std::make_unique<Graphics::Material>(resourceFile);
    try {
        resourceFile = Core::ReadFile(filePath);
    }
    catch (std::exception& e) {
        Core::Log::Instance().Out(Core::LogLevel::Error) << "Failed to load material resource: \n" << e.what() << '\n';
        return nullptr;
    }

    try
    {
        try
        {
            nlohmann::json data = nlohmann::json::parse(Core::ReadFile(filePath));

            const std::string& shaderAssetFilepath = data["Shader"].get<std::string>();
            const std::string& texturesAssetFilepath = data["Textures"].get<std::string>();
            const std::string& shaderParametersAssetFilepath = data["ShaderParameters"].get<std::string>();

            material->LoadShader(shaderAssetFilepath);
            material->LoadTextures(texturesAssetFilepath);
            material->LoadShaderParameters(shaderParametersAssetFilepath);

        }
        catch (nlohmann::json::exception& e)
        {
            Core::Log::Instance().Out(Core::LogLevel::Error) << "Failed to parse material asset file: " << e.what() << '\n';
        }


        return material;
    }
    catch (nlohmann::json::exception& e)
    {
        Core::Log::Instance().Out(Core::LogLevel::Error) << "Failed to parse material resource file: \n" << e.what() << '\n';
    }

    return nullptr;
}