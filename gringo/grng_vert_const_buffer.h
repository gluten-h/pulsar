#pragma once

#include "grng_const_buffer.h"


template <typename T>
class grng_vert_const_buffer : public GRNG_CONST_BUFFER<T>
{
private:
	void		copy_assign(const grng_vert_const_buffer &b)
	{
		this->buffer = b.buffer;
		this->slot = b.slot;
		this->data_ptr = b.data_ptr;
		this->data_size = b.data_size;
		if (this->buffer)
			this->buffer->AddRef();
	}

public:
	grng_vert_const_buffer	&operator=(const grng_vert_const_buffer &b)
	{
		if (this->buffer != b.buffer)
			this->remove_data_memory();
		this->copy_assign(b);

		return (*this);
	}

	grng_vert_const_buffer(const grng_vert_const_buffer &b) : GRNG_CONST_BUFFER<T>()
	{
		this->copy_assign(b);
	}
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
