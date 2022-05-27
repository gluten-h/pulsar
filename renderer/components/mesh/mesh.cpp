
#include "mesh.h"
#include "gfx/gfx.h"


pulsar::mesh::mesh(LPCWSTR file, pulsar::MESH_FILE_FORMAT file_format)
{
	this->set(file, file_format);
}

pulsar::mesh::~mesh()
{
	this->free();
}

void	pulsar::mesh::bind() const
{
	UINT v_stride = sizeof(mesh::mesh_data::vert_data);
	UINT v_offset = 0;
	pulsar::gfx::instance().device_context()->IASetVertexBuffers(0u, 1u, &this->mp_vertex_buffer, &v_stride, &v_offset);
	pulsar::gfx::instance().device_context()->IASetIndexBuffer(this->mp_index_buffer, DXGI_FORMAT_R32_UINT, 0u);
	pulsar::gfx::instance().device_context()->IASetPrimitiveTopology(this->m_primitive_topology);
}

void	pulsar::mesh::unbind() const
{
	UINT v_stride = 0u;
	UINT v_offset = 0u;
	ID3D11Buffer *null_ptr[1] = { NULL };
	pulsar::gfx::instance().device_context()->IASetVertexBuffers(0u, 1u, null_ptr, &v_stride, &v_offset);
	pulsar::gfx::instance().device_context()->IASetIndexBuffer(NULL, DXGI_FORMAT_R32_UINT, 0u);
}
