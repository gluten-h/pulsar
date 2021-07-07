#pragma once

#include "grng_bindable.h"


template <typename T>
class grng_const_buffer : public GRNG_BINDABLE
{
protected:
	ID3D11Buffer			*buffer = NULL;
	UINT					slot = 0u;
	const T					*data_ptr = NULL;
	size_t					data_size = 0;

private:
	void	set_data_memory(const T &data)
	{
		this->data_ptr = &data;
		this->data_size = sizeof(data);

		D3D11_BUFFER_DESC bd;
		bd.ByteWidth = sizeof(T);
		bd.StructureByteStride = 0u;
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0u;

		D3D11_SUBRESOURCE_DATA sd;
		sd.pSysMem = &data;
		sd.SysMemPitch = 0u;
		sd.SysMemSlicePitch = 0u;
		HRESULT hr = this->device->CreateBuffer(&bd, &sd, &this->buffer);
	}

	void	set_data_memory()
	{
		D3D11_BUFFER_DESC bd;
		bd.ByteWidth = sizeof(T);
		bd.StructureByteStride = 0u;
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.MiscFlags = 0u;

		HRESULT hr = this->device->CreateBuffer(&bd, NULL, &this->buffer);
	}


	void	remove_data_memory()
	{
		if (this->buffer)
		{
			this->buffer->Release();
			this->buffer = NULL;
		}
	}

public:
	grng_const_buffer(UINT slot) : GRNG_BINDABLE()
	{
		this->set_data_memory();
		this->set_slot(slot);
	}

	grng_const_buffer(const T &data, UINT slot) : GRNG_BINDABLE()
	{
		this->set_data_memory(data);
		this->set_slot(slot);
	}

	~grng_const_buffer()
	{
		this->remove_data_memory();
	}

	void	destroy() override
	{
		this->remove_data_memory();
	}

	void	update()
	{
		D3D11_MAPPED_SUBRESOURCE ms;
		this->device_context->Map(this->buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms);
		memcpy(ms.pData, this->data_ptr, this->data_size);
		this->device_context->Unmap(this->buffer, 0u);
	}
	void	update(const T &data)
	{
		this->data_ptr = &data;
		this->data_size = sizeof(data);

		D3D11_MAPPED_SUBRESOURCE ms;
		this->device_context->Map(this->buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms);
		memcpy(ms.pData, &data, sizeof(data));
		this->device_context->Unmap(this->buffer, 0u);
	}

	void	set_data(const T &data)
	{
		this->remove_data_memory();
		this->set_data_memory(data);
	}

	void	set_slot(UINT slot)
	{
		this->slot = slot;
	}
};

template <typename T>
using GRNG_CONST_BUFFER = grng_const_buffer<T>;


template <typename T>
class grng_vert_const_buffer : public GRNG_CONST_BUFFER<T>
{
public:
	grng_vert_const_buffer(UINT slot = 0u) : GRNG_CONST_BUFFER<T>(slot)
	{
		this->type = GRNG_BINDABLE_TYPE::VERT_CONST_BUFFER;
	}
	grng_vert_const_buffer(const T &data, UINT slot = 0u) : GRNG_CONST_BUFFER<T>(data, slot)
	{
		this->type = GRNG_BINDABLE_TYPE::VERT_CONST_BUFFER;
	}


	static GRNG_BINDABLE		*create_manager_ptr()
	{
		grng_vert_const_buffer *buffer = new grng_vert_const_buffer;

		return (buffer);
	}


	void	bind() override
	{
		this->device_context->VSSetConstantBuffers(this->slot, 1, &this->buffer);
	}
};

template <typename T>
using GRNG_VERT_CONST_BUFFER = grng_vert_const_buffer<T>;


template <typename T>
class grng_frag_const_buffer : public GRNG_CONST_BUFFER<T>
{
public:
	grng_frag_const_buffer(UINT slot = 0u) : GRNG_CONST_BUFFER<T>(slot)
	{
		this->type = GRNG_BINDABLE_TYPE::FRAG_CONST_BUFFER;
	}
	grng_frag_const_buffer(const T &data, UINT slot = 0u) : GRNG_CONST_BUFFER<T>(data, slot)
	{
		this->type = GRNG_BINDABLE_TYPE::FRAG_CONST_BUFFER;
	}


	static GRNG_BINDABLE		*create_manager_ptr()
	{
		grng_frag_const_buffer *buffer = new grng_frag_const_buffer;

		return (buffer);
	}


	void	bind() override
	{
		this->device_context->PSSetConstantBuffers(this->slot, 1, &this->buffer);
	}
};

template <typename T>
using GRNG_FRAG_CONST_BUFFER = grng_frag_const_buffer<T>;
