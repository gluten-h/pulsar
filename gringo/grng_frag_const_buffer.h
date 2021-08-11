#pragma once

#include "grng_const_buffer.h"
#include "grng_bindable_entity.h"


template <typename T>
class grng_frag_const_buffer : public GRNG_CONST_BUFFER<T>
{
private:
	void		copy_assign(const grng_frag_const_buffer &b)
	{
		this->buffer = b.buffer;
		this->slot = b.slot;
		this->data_ptr = b.data_ptr;
		this->data_size = b.data_size;
		if (this->buffer)
			this->buffer->AddRef();
	}

protected:
	void		remove_from_entities() override
	{
		for (auto &it : this->entities)
			it->_remove_bindable_ignore_entity(this);
		this->entities.clear();
	}

public:
	using GRNG_BINDABLE::bind;

public:
	grng_frag_const_buffer	&operator=(const grng_frag_const_buffer &b)
	{
		if (this->buffer != b.buffer)
			this->remove_data_memory();
		this->copy_assign(b);

		return (*this);
	}

	grng_frag_const_buffer(const grng_frag_const_buffer &b) : GRNG_CONST_BUFFER<T>()
	{
		this->type = GRNG_BINDABLE_TYPE::FRAG_CONST_BUFFER;
		this->copy_assign(b);
	}
	grng_frag_const_buffer(UINT slot = 0u) : GRNG_CONST_BUFFER<T>(slot)
	{
		this->type = GRNG_BINDABLE_TYPE::FRAG_CONST_BUFFER;
	}
	grng_frag_const_buffer(const T &data, UINT slot = 0u) : GRNG_CONST_BUFFER<T>(data, slot)
	{
		this->type = GRNG_BINDABLE_TYPE::FRAG_CONST_BUFFER;
	}


	static grng_frag_const_buffer<T>		*create()
	{
		grng_frag_const_buffer<T> *buffer = new grng_frag_const_buffer<T>;
		buffer->id = GRNG_BM.add(buffer);
		if (buffer->id == -1)
		{
			delete buffer;
			return (NULL);
		}
		buffer->is_alloc = true;

		return (buffer);
	}


	void		bind() const override
	{
		this->device_context->PSSetConstantBuffers(this->slot, 1u, &this->buffer);
		GRNG_BINDABLE::add_unbind(*this);
	}

	void		unbind() const override
	{
		this->device_context->PSSetConstantBuffers(this->slot, 0u, NULL);
	}
};

template <typename T>
using GRNG_FRAG_CONST_BUFFER = grng_frag_const_buffer<T>;
