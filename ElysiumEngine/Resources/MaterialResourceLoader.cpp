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
        nlohmann::json data = nlohmann::json::parse(Core::ReadFile(filePath));

        const std::string& shaderAssetFilepath = data["Shader"].get<std::string>();
        const nlohmann::json& texturesAsset = data["Textures"];
        const nlohmann::json& shaderParameters = data["ShaderParameters"];

        material->LoadShader(shaderAssetFilepath);
        material->LoadTextures(texturesAsset);
        material->LoadShaderParameters(shaderParameters);


        return material;
    }
    catch (nlohmann::json::exception& e)
    {
        Core::Log::Instance().Out(Core::LogLevel::Error) << "Failed to parse material resource file: \n" << e.what() << '\n';
    }

    return nullptr;
}