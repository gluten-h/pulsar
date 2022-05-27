
#include "mesh.h"
#include "filesystem/filesystem.h"


void	pulsar::mesh::free()
{
	this->m_mesh_data.clear();

	if (this->mp_vertex_buffer)
	{
		this->mp_vertex_buffer->Release();
		this->mp_vertex_buffer = NULL;
	}
	if (this->mp_index_buffer)
	{
		this->mp_index_buffer->Release();
		this->mp_index_buffer = NULL;
	}
}

void	pulsar::mesh::set(LPCWSTR file, pulsar::MESH_FILE_FORMAT file_format)
{
	this->free();

	switch (file_format)
	{
		case pulsar::MESH_FILE_FORMAT::OBJ:
		{
			if (this->load_mesh_obj(pulsar::filesystem::absolute_path(file).c_str()))
				this->create_mesh();

			break;
		}
	}
}

void	pulsar::mesh::set_primitive_topology(D3D_PRIMITIVE_TOPOLOGY primitive_topology)
{
	this->m_primitive_topology = primitive_topology;
}

UINT	pulsar::mesh::get_index_count() const noexcept
{
	return ((UINT)this->m_mesh_data.m_indices.size());
}
