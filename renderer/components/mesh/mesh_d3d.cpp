
#include "mesh.h"
#include "exceptions/gfx_exception.h"


void	PULSAR::mesh::create_mesh()
{
	D3D11_BUFFER_DESC vbd;
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&vbd, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&ibd, sizeof(D3D11_BUFFER_DESC));

	vbd.ByteWidth = sizeof(mesh::mesh_data::vert_data) * (UINT32)this->m_mesh_data.m_verts.size();
	vbd.StructureByteStride = sizeof(mesh::mesh_data::vert_data);
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0u;
	vbd.MiscFlags = 0u;

	ibd.ByteWidth = sizeof(UINT32) * (UINT32)this->m_mesh_data.m_indices.size();
	ibd.StructureByteStride = sizeof(UINT32);
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;

	D3D11_SUBRESOURCE_DATA vsd;
	D3D11_SUBRESOURCE_DATA isd;
	ZeroMemory(&vsd, sizeof(D3D11_SUBRESOURCE_DATA));
	ZeroMemory(&isd, sizeof(D3D11_SUBRESOURCE_DATA));
	vsd.pSysMem = this->m_mesh_data.m_verts.data();
	isd.pSysMem = this->m_mesh_data.m_indices.data();

	GFX_ASSERT(PULSAR::gfx::get().device()->CreateBuffer(&vbd, &vsd, &this->mp_vertex_buffer));
	GFX_ASSERT(PULSAR::gfx::get().device()->CreateBuffer(&ibd, &isd, &this->mp_index_buffer));
}
