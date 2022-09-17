
#include "quad.h"


pulsar::quad::quad()
{
	this->m_mesh_data.m_verts.reserve(4u);
	this->m_mesh_data.m_indices.reserve(6u);
	this->m_mesh_data.m_mesh_specs = { true, true };

	this->m_mesh_data.m_verts.push_back({{-1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}});

	this->m_mesh_data.m_indices.push_back(0u);
	this->m_mesh_data.m_indices.push_back(1u);
	this->m_mesh_data.m_indices.push_back(2u);
	this->m_mesh_data.m_indices.push_back(0u);
	this->m_mesh_data.m_indices.push_back(2u);
	this->m_mesh_data.m_indices.push_back(3u);

	this->create_mesh();
}
