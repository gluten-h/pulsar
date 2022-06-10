
#include "mesh.h"
#include "filesystem/filesystem.h"
#include "exceptions/gfx_exception.h"


void	pulsar::mesh::create_mesh()
{
	D3D11_BUFFER_DESC vbd;
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&vbd, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&ibd, sizeof(D3D11_BUFFER_DESC));

	vbd.ByteWidth = sizeof(mesh::mesh_data::vert_data) * (UINT32)this->m_mesh_data.m_verts.size();
	vbd.StructureByteStride = sizeof(mesh::mesh_data::vert_data);
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0u;
	vbd.MiscFlags = 0u;

	ibd.ByteWidth = sizeof(UINT32) * (UINT32)this->m_mesh_data.m_indices.size();
	ibd.StructureByteStride = sizeof(UINT32);
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;

	D3D11_SUBRESOURCE_DATA vsd;
	D3D11_SUBRESOURCE_DATA isd;
	ZeroMemory(&vsd, sizeof(D3D11_SUBRESOURCE_DATA));
	ZeroMemory(&isd, sizeof(D3D11_SUBRESOURCE_DATA));
	vsd.pSysMem = this->m_mesh_data.m_verts.data();
	isd.pSysMem = this->m_mesh_data.m_indices.data();

	GFX_ASSERT(pulsar::gfx::instance().device()->CreateBuffer(&vbd, &vsd, &this->mp_vertex_buffer));
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateBuffer(&ibd, &isd, &this->mp_index_buffer));
}

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
