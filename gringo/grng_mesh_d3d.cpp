
#include "grng_mesh.h"


void		grng_mesh::bind()
{
	UINT v_stride = sizeof(grng_mesh::GRNG_MESH_DATA::GRNG_VERT_DATA);
	UINT v_offset = 0;
	this->device_context->IASetVertexBuffers(0, 1, &this->v_buffer, &v_stride, &v_offset);
	this->device_context->IASetIndexBuffer(this->i_buffer, DXGI_FORMAT_R32_UINT, 0);
	this->device_context->IASetPrimitiveTopology(this->primitive_topology);
}

void		grng_mesh::create_buffer()
{
	D3D11_BUFFER_DESC vbd;
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&vbd, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&ibd, sizeof(D3D11_BUFFER_DESC));

	vbd.ByteWidth = sizeof(grng_mesh::GRNG_MESH_DATA::GRNG_VERT_DATA) * this->mesh.verts.size();
	vbd.StructureByteStride = sizeof(grng_mesh::GRNG_MESH_DATA::GRNG_VERT_DATA);
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0u;
	vbd.MiscFlags = 0u;

	ibd.ByteWidth = sizeof(UINT32) * this->mesh.indices.size();
	ibd.StructureByteStride = sizeof(UINT32);
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;

	D3D11_SUBRESOURCE_DATA vsd;
	D3D11_SUBRESOURCE_DATA isd;
	ZeroMemory(&vsd, sizeof(D3D11_SUBRESOURCE_DATA));
	ZeroMemory(&isd, sizeof(D3D11_SUBRESOURCE_DATA));
	vsd.pSysMem = this->mesh.verts.data();
	isd.pSysMem = this->mesh.indices.data();

	HRESULT hr;
	hr = this->device->CreateBuffer(&vbd, &vsd, &this->v_buffer);
	hr = this->device->CreateBuffer(&ibd, &isd, &this->i_buffer);
}

void		grng_mesh::draw()
{
	this->device_context->DrawIndexed((UINT)this->mesh.indices.size(), 0u, 0);
}
