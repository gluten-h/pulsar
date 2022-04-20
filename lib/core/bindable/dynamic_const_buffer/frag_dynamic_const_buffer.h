#pragma once

#include "dynamic_const_buffer.h"


namespace PULSAR
{
	class frag_dynamic_const_buffer : public PULSAR::dynamic_const_buffer
	{
	public:
		using PULSAR::BINDABLE::bind;

	public:
		frag_dynamic_const_buffer	&operator=(const frag_dynamic_const_buffer &b) = delete;
		frag_dynamic_const_buffer(const frag_dynamic_const_buffer &b) = delete;

		frag_dynamic_const_buffer(UINT slot = 0u) : PULSAR::dynamic_const_buffer(slot)
		{
			this->type = PULSAR::BINDABLE_TYPE::FRAG_DYNAMIC_CONST_BUFFER;
		}
		frag_dynamic_const_buffer(PULSAR::dcb::buffer *dcb_buffer, UINT slot = 0u) : PULSAR::dynamic_const_buffer(dcb_buffer, slot)
		{
			this->type = PULSAR::BINDABLE_TYPE::FRAG_DYNAMIC_CONST_BUFFER;
		}

		void	bind() const override
		{
			this->device_context->PSSetConstantBuffers(this->m_slot, 1u, &this->mp_buffer);
			BINDABLE::add_unbind(*this);
		}

		void	unbind() const override
		{
			static ID3D11Buffer *null_ptr[1] = { NULL };
			this->device_context->PSSetConstantBuffers(this->m_slot, 0u, null_ptr);
		}
	};
}
