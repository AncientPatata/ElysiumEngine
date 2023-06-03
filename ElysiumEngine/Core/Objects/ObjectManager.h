#pragma once
#include "Object.h"

#include <functional>
#include <unordered_map>


namespace Core {


    class EObjectFactory {
    public:
        template <typename T>
        static T* Create() {
            static_assert(std::is_base_of<EObject, T>::value, "T must inherit from EObject");
            return new T();
        }
    };
    class EObjectManager {
    public:
        template <typename T>
        T* Create() {
            T* eObject = EObjectFactory::Create<T>();
            eObjects[eObject->GetID()] = eObject;
            return eObject;
        }

        EObject* Get(std::size_t id) {
            if (eObjects.find(id) != eObjects.end()) {
                return eObjects[id];
            }
            return nullptr;
        }

        void Destroy(std::size_t id) {
            if (eObjects.find(id) != eObjects.end()) {
                delete eObjects[id];
                eObjects.erase(id);
            }
        }

    private:
        std::unordered_map<std::size_t, EObject*> eObjects;
    };

}