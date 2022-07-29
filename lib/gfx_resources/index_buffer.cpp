
#include "index_buffer.h"


pulsar::index_buffer::index_buffer(const void *data, UINT size)
{
	this->create_index_buffer(data, size);
}

void	pulsar::index_buffer::create_index_buffer(const void *data, UINT size)
{
	D3D11_BUFFER_DESC bd;
	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));

	bd.ByteWidth = size;
	bd.StructureByteStride = sizeof(UINT);
	bd.Usage = D3D11_USAGE_IMMUTABLE;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	sd.pSysMem = data;
	this->create_buffer(&bd, &sd);
}

void	pulsar::index_buffer::set(const void *data, UINT size)
{
	this->destroy_buffer();
	this->create_index_buffer(data, size);
}
