// MaterialResourceLoader.h
#pragma once

#include "../Core/ResourceManager/ResourceLoader.h"
#include "../Graphics/Material.h"

namespace Resources {

    class MaterialResourceLoader : public Core::ResourceLoader {
    public:
        std::unique_ptr<Core::Resource> Load(const std::string& filePath) override;

        static std::string GetResourceType() {
            return "Material";
        }
    };

}