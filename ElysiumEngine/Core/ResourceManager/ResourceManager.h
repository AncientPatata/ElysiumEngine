#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "Resource.h"
#include "ResourceLoader.h"

namespace Core {

    class ResourceManager {
    public:

        static ResourceManager& Instance() {
            static ResourceManager instance;
            return instance;
        }

        template <typename T>
        void RegisterResourceLoader() {
            static_assert(std::is_base_of<ResourceLoader, T>::value, "T must inherit from ResourceLoader");
            auto loader = std::make_unique<T>();
            m_loaders[T::GetResourceType()] = std::move(loader);
        }

        template <typename T>
        T* Load(const std::string& filePath) {
            // Check if the resource is already loaded
            if (m_resources.find(filePath) != m_resources.end()) {
                return static_cast<T*>(m_resources[filePath].get());
            }

            // Find the appropriate resource loader
            auto loaderIt = m_loaders.find(T::GetResourceType());
            if (loaderIt == m_loaders.end()) {
                // No resource loader found for the resource type
                return nullptr;
            }

            // Create and load the resource
            std::unique_ptr<Resource> resource = loaderIt->second->Load(filePath);
            if (!resource) {
                // Handle resource loading failure
                return nullptr;
            }

            // Store the resource in the manager
            m_resources[filePath] = std::move(resource);
            return static_cast<T*>(m_resources[filePath].get());
        }

        template <typename T>
        T* Get(const std::string& filePath) {
            // Check if the resource is already loaded
            if (m_resources.find(filePath) != m_resources.end()) {
                return static_cast<T*>(m_resources[filePath].get());
            }

            // Resource not found
            return nullptr;
        }

        void Unload(const std::string& filePath) {
            // Check if the resource is loaded
            auto it = m_resources.find(filePath);
            if (it != m_resources.end()) {
                m_resources.erase(it);
            }
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<Resource>> m_resources;
        std::unordered_map<std::string, std::unique_ptr<ResourceLoader>> m_loaders;
        ResourceManager() = default;
        ~ResourceManager() = default;
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
    };

} // namespace Core