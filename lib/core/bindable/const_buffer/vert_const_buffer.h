#pragma once

#include "const_buffer.h"
#include "bindable_entity.h"


namespace PULSAR
{
	template <typename T>
	class VERT_CONST_BUFFER : public PULSAR::CONST_BUFFER<T>
	{
	private:
		void		copy_assign(const VERT_CONST_BUFFER &b)
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
		using PULSAR::BINDABLE::bind;

	public:
		VERT_CONST_BUFFER	&operator=(const VERT_CONST_BUFFER &b)
		{
			if (this->buffer != b.buffer)
				this->remove_data_memory();
			this->copy_assign(b);

			return (*this);
		}

		VERT_CONST_BUFFER(const VERT_CONST_BUFFER &b) : PULSAR::CONST_BUFFER<T>()
		{
			this->type = PULSAR::BINDABLE_TYPE::VERT_CONST_BUFFER;
			this->copy_assign(b);
		}
		VERT_CONST_BUFFER(UINT slot = 0u) : PULSAR::CONST_BUFFER<T>(slot)
		{
			this->type = PULSAR::BINDABLE_TYPE::VERT_CONST_BUFFER;
		}
		VERT_CONST_BUFFER(const T &data, UINT slot = 0u) : PULSAR::CONST_BUFFER<T>(data, slot)
		{
			this->type = PULSAR::BINDABLE_TYPE::VERT_CONST_BUFFER;
		}


		static VERT_CONST_BUFFER<T>		*create()
		{
			return ((PULSAR::VERT_CONST_BUFFER<T>*)PULSAR::BINDABLE::add_to_manager(new PULSAR::VERT_CONST_BUFFER<T>));
		}


		void		bind() const override
		{
			this->device_context->VSSetConstantBuffers(this->slot, 1u, &this->buffer);
			BINDABLE::add_unbind(*this);
		}

		void		unbind() const override
		{
			this->device_context->VSSetConstantBuffers(this->slot, 0u, NULL);
		}
	};
}
