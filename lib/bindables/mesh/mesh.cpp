
#include "mesh.h"


PULSAR::mesh::mesh(LPCWSTR file, PULSAR::MESH_FILE_FORMAT file_format)
{
	this->set(file, file_format);
}

PULSAR::mesh::~mesh()
{
	this->free();
}

void	PULSAR::mesh::bind() const
{
	UINT v_stride = sizeof(mesh::mesh_data::vert_data);
	UINT v_offset = 0;
	PULSAR::gfx::get().device_context()->IASetVertexBuffers(0u, 1u, &this->mp_vertex_buffer, &v_stride, &v_offset);
	PULSAR::gfx::get().device_context()->IASetIndexBuffer(this->mp_index_buffer, DXGI_FORMAT_R32_UINT, 0u);
	PULSAR::gfx::get().device_context()->IASetPrimitiveTopology(this->m_primitive_topology);
}

void	PULSAR::mesh::unbind() const
{
	static ID3D11Buffer *null_ptr[1] = { NULL };
	PULSAR::gfx::get().device_context()->IASetVertexBuffers(0u, 1u, null_ptr, NULL, NULL);
	PULSAR::gfx::get().device_context()->IASetIndexBuffer(NULL, DXGI_FORMAT_R32_UINT, 0u);
}
