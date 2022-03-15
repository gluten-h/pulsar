#pragma once

#include "bindable.h"


namespace PULSAR
{
	template <typename T>
	class CONST_BUFFER : public PULSAR::BINDABLE
	{
	protected:
		ID3D11Buffer	*buffer = NULL;
		UINT			slot = 0u;
		const T			*data_ptr = NULL;
		size_t			data_size = 0;


		void	set_data_memory(const T &data)
		{
			HRESULT hr;

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
			GFX_ASSERT(this->device->CreateBuffer(&bd, &sd, &this->buffer));
		}

		void	set_data_memory()
		{
			HRESULT hr;

			D3D11_BUFFER_DESC bd;
			bd.ByteWidth = sizeof(T);
			bd.StructureByteStride = 0u;
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bd.MiscFlags = 0u;

			GFX_ASSERT(this->device->CreateBuffer(&bd, NULL, &this->buffer));
		}


		void	remove_data_memory()
		{
			if (this->buffer)
			{
				ULONG ref_count = this->buffer->Release();
				if (ref_count == 0)
					this->buffer = NULL;
			}
		}


		void		remove_from_entities() override
		{
			for (auto &it : this->entities)
				it->_remove_bindable_ignore_entity(this);
			this->entities.clear();
		}

	public:
		CONST_BUFFER	&operator=(const CONST_BUFFER &b) = delete;
		CONST_BUFFER(const CONST_BUFFER &b) = delete;

		CONST_BUFFER(UINT slot = 0u) : PULSAR::BINDABLE()
		{
			this->set_data_memory();
			this->set_slot(slot);
		}

		CONST_BUFFER(const T &data, UINT slot = 0u) : PULSAR::BINDABLE()
		{
			this->set_data_memory(data);
			this->set_slot(slot);
		}

		~CONST_BUFFER()
		{
			this->remove_data_memory();
		}

		void	update()
		{
			D3D11_MAPPED_SUBRESOURCE ms;
			GFX_ASSERT(this->device_context->Map(this->buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms));
			memcpy(ms.pData, this->data_ptr, this->data_size);
			this->device_context->Unmap(this->buffer, 0u);
		}
		void	update(const T &data)
		{
			this->data_ptr = &data;
			this->data_size = sizeof(data);

			D3D11_MAPPED_SUBRESOURCE ms;
			GFX_ASSERT(this->device_context->Map(this->buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms));
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
}
