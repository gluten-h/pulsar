#pragma once

#include "dynamic_const_buffer.h"


namespace PULSAR
{
	class vert_dynamic_const_buffer : public PULSAR::dynamic_const_buffer
	{
	public:
		using PULSAR::BINDABLE::bind;

	public:
		vert_dynamic_const_buffer	&operator=(const vert_dynamic_const_buffer &b) = delete;
		vert_dynamic_const_buffer(const vert_dynamic_const_buffer &b) = delete;

		vert_dynamic_const_buffer(UINT slot = 0u) : PULSAR::dynamic_const_buffer(slot)
		{
			this->type = PULSAR::BINDABLE_TYPE::VERT_DYNAMIC_CONST_BUFFER;
		}
		vert_dynamic_const_buffer(PULSAR::dcb::buffer *dcb_buffer, UINT slot = 0u) : PULSAR::dynamic_const_buffer(dcb_buffer, slot)
		{
			this->type = PULSAR::BINDABLE_TYPE::VERT_DYNAMIC_CONST_BUFFER;
		}

		void	bind() const override
		{
			this->device_context->VSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
			BINDABLE::add_unbind(*this);
		}

		void	unbind() const override
		{
			static ID3D11Buffer *null_ptr[1] = { NULL };
			this->device_context->VSSetConstantBuffers(this->m_slot, 0u, null_ptr);
		}
	};
}
