
#include "cube.h"


pulsar::cube::cube()
{
	this->m_mesh_data.m_verts.reserve(36u);

	this->m_mesh_data.m_verts.push_back({{1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}});

	this->m_mesh_data.m_verts.push_back({{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}});

	this->m_mesh_data.m_verts.push_back({{-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, -1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}});

	this->m_mesh_data.m_verts.push_back({{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}});

	this->m_mesh_data.m_verts.push_back({{-1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}});

	this->m_mesh_data.m_verts.push_back({{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}});

	this->m_mesh_data.m_verts.push_back({{1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}});

	this->m_mesh_data.m_verts.push_back({{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}});

	this->m_mesh_data.m_verts.push_back({{-1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, 1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}});

	this->m_mesh_data.m_verts.push_back({{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}});

	this->m_mesh_data.m_verts.push_back({{-1.0f, -1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}});

	this->m_mesh_data.m_verts.push_back({{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}});
	this->m_mesh_data.m_verts.push_back({{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}});
	this->m_mesh_data.m_verts.push_back({{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}});

	int i = -1;
	while (++i < 36u)
		this->m_mesh_data.m_indices.push_back(i);
	this->m_mesh_data.m_mesh_specs = { true, true };

	this->create_mesh();
}
