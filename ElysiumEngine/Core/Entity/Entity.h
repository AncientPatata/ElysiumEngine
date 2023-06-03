#pragma once
#include "../Objects/Object.h"
#include <vector>
#include "EntityComponent.h"

namespace Core {

    class EEntity : public EObject {
    public:
        EEntity() : EObject() {}

        void AddComponent(EEntityComponent* component) {
            components.push_back(component);
        }

        // Additional entity-specific methods and members

    private:
        std::vector<EEntityComponent*> components;
    };

}