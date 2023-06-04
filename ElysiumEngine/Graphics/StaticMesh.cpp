#include "StaticMesh.h"


using namespace Renderer;

StaticMesh::StaticMesh(Graphics::Geometry* geometry, Graphics::Material* material, Math::Transform* transform)
	: Core::EObject(), m_geometry(geometry), m_material(material), m_transform(transform)
{
}

void StaticMesh::Draw() const
{
	m_geometry->Draw();
}
