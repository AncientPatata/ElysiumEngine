#pragma once
#include "../Core/Objects/Object.h"
#include "../Core/ResourceManager/ResourceManager.h"
#include "Geometry.h"
#include "Material.h"
#include "../Core/Math/Math.h"

namespace Renderer {
	class StaticMesh : public Core::EObject {
	public:
		StaticMesh(Graphics::Geometry* geometry, Graphics::Material* material, Math::Transform* transform);
		~StaticMesh() = default;

		void Draw() const;

		Graphics::Material* GetMaterial() const { return m_material; }
		Math::Transform* GetTransform() const { return m_transform; }
		Graphics::Geometry* GetGeometry() const { return m_geometry; }


	private:
		Graphics::Geometry* m_geometry;
		Graphics::Material* m_material;
		Math::Transform* m_transform;
	};
}