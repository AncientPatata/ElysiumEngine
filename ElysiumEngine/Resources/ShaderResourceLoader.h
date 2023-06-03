#pragma once

#include "../Core/ResourceManager/ResourceLoader.h"
#include "../Graphics/Shader.h"

namespace Resources {

	class ShaderResourceLoader : public Core::ResourceLoader {
	public:
		std::unique_ptr<Core::Resource> Load(const std::string& filePath) override;

		static std::string GetResourceType() {
			return "Shader";
		}
	};

}

