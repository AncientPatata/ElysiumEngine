#pragma once

#include <functional>

namespace Core {

    class EObject {
    public:
        EObject() {
            uniqueID = std::hash<const EObject*>()(this);
        }

        std::size_t GetID() const {
            return uniqueID;
        }

    private:
        std::size_t uniqueID;
    };

}