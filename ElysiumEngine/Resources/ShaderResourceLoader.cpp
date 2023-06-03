#include "ShaderResourceLoader.h"

#include "../Core/Utils.h"
#include "nlohmann/json.hpp"
#include "../Core/Log.h"



std::unique_ptr<Core::Resource> Resources::ShaderResourceLoader::Load(const std::string& filePath)
{
    std::string resourceFile;
    try {
        resourceFile = Core::ReadFile(filePath);
    }
    catch (std::exception& e) {
		Core::Log::Instance().Out(Core::LogLevel::Error) << "Failed to load shader resource : \n" << e.what() << '\n';
        return nullptr;
	}

    try
    {
        nlohmann::json data = nlohmann::json::parse(resourceFile);
        const std::string& vertexSourcePath = data["Vertex Shader Source"].get<std::string>();
        const std::string& fragmentSourcePath = data["Fragment Shader Source"].get<std::string>();
        // Load the shader source code from the file
        std::string vertexSource = Core::ReadFile(vertexSourcePath);
        std::string fragmentSource = Core::ReadFile(fragmentSourcePath);
        // Create a new ShaderResource object
        std::unique_ptr<Core::Resource> resource = std::make_unique<Graphics::Shader>(filePath, vertexSource, fragmentSource);

        return resource;

    }
    catch (nlohmann::json::exception& e)
    {
        Core::Log::Instance().Out(Core::LogLevel::Error) << "Failed to parse shader resource file : \n" << e.what() << '\n';
    }

    return nullptr;

 }

