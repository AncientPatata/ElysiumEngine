#pragma once
#include "Resource.h"

#include <unordered_map>
#include <string>
#include <memory>

namespace Core {

    class ResourceLoader {
    public:
        virtual ~ResourceLoader() = default;
        virtual std::unique_ptr<Resource> Load(const std::string& filePath) = 0;
    };

}