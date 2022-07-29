#pragma once

#include "buffer_resource.h"


namespace pulsar
{
	template <typename T>
	class vertex_buffer : public pulsar::buffer_resource
	{
	private:
		void	create_vertex_buffer(const void *data, UINT size)
		{
			D3D11_BUFFER_DESC bd;
			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));

			bd.ByteWidth = size;
			bd.StructureByteStride = sizeof(T);
			bd.Usage = D3D11_USAGE_IMMUTABLE;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0u;
			bd.MiscFlags = 0u;
			sd.pSysMem = data;
			this->create_buffer(bd, sd);
		}

	public:
		vertex_buffer &operator=(const vertex_buffer&) = delete;
		vertex_buffer &operator=(vertex_buffer&&) = delete;
		vertex_buffer(const vertex_buffer&) = delete;
		vertex_buffer(vertex_buffer&&) = delete;
		vertex_buffer() = default;
		vertex_buffer(const void *data, UINT size)
		{
			this->create_vbuffer();
		}
		~vertex_buffer() = default;

		void	set(const void *data, UINT size)
		{
			this->destroy_buffer();
			this->create_vertex_buffer(data, size);
		}
	};
}
