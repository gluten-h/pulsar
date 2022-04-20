#pragma once

#include "bindable.h"
#include "dcb/dcb_buffer.h"


namespace PULSAR
{
	class dynamic_const_buffer : public PULSAR::BINDABLE
	{
	protected:
		ID3D11Buffer *mp_buffer = NULL;
		PULSAR::dcb::buffer	*mp_dcb_buffer = NULL;
		UINT	m_slot = 0u;


		void	set_buffer(PULSAR::dcb::buffer *dcb_buffer)
		{
			if (!dcb_buffer)
				return;

			this->mp_dcb_buffer = dcb_buffer;

			HRESULT hr;

			D3D11_BUFFER_DESC bd;
			bd.ByteWidth = (UINT)dcb_buffer->size();
			bd.StructureByteStride = 0u;
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bd.MiscFlags = 0u;

			D3D11_SUBRESOURCE_DATA sd;
			sd.pSysMem = dcb_buffer->data();
			sd.SysMemPitch = 0u;
			sd.SysMemSlicePitch = 0u;
			GFX_ASSERT(this->device->CreateBuffer(&bd, &sd, &this->mp_buffer));
		}

		void	release_buffer()
		{
			if (this->mp_buffer)
			{
				ULONG ref_count = this->mp_buffer->Release();
				if (ref_count == 0)
					this->mp_buffer = NULL;
			}
		}


		void		remove_from_entities() override
		{
			for (auto &it : this->entities)
				it->_remove_bindable_ignore_entity(this);
			this->entities.clear();
		}

	public:
		dynamic_const_buffer	&operator=(const dynamic_const_buffer &b) = delete;
		dynamic_const_buffer(const dynamic_const_buffer &b) = delete;

		dynamic_const_buffer(UINT slot = 0u) : PULSAR::BINDABLE()
		{
			this->m_slot = slot;
		}
		dynamic_const_buffer(PULSAR::dcb::buffer *dcb_buffer, UINT slot = 0u) : PULSAR::BINDABLE()
		{
			this->set_buffer(dcb_buffer);
			this->m_slot = slot;
		}
		~dynamic_const_buffer()
		{
			this->release_buffer();
		}

		void	update()
		{
			if (!this->mp_dcb_buffer)
				return;

			D3D11_MAPPED_SUBRESOURCE ms;
			GFX_ASSERT(this->device_context->Map(this->mp_buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms));
			memcpy(ms.pData, this->mp_dcb_buffer->data(), this->mp_dcb_buffer->size());
			this->device_context->Unmap(this->mp_buffer, 0u);

			this->mp_dcb_buffer->set_updated();
		}

		void	set_dcb_buffer(PULSAR::dcb::buffer *dcb_buffer)
		{
			this->release_buffer();
			this->set_buffer(dcb_buffer);
		}
		void	set_slot(UINT slot)
		{
			this->m_slot = slot;
		}
		bool	is_modified() const noexcept
		{
			return (this->mp_dcb_buffer && this->mp_dcb_buffer->is_modified());
		}
	};
}
