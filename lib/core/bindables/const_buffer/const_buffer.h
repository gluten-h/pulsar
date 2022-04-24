#pragma once

#include "bindable/bindable.h"


namespace PULSAR
{
	template <typename T>
	class const_buffer : public PULSAR::bindable
	{
	protected:
		ID3D11Buffer *mp_buffer = NULL;
		UINT m_slot = 0u;
		const T *mp_data = NULL;
		size_t m_data_size = 0;

	protected:
		void	create_buffer(const T &data)
		{
			HRESULT hr;

			this->mp_data = &data;
			this->m_data_size = sizeof(data);

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
			GFX_ASSERT(PULSAR::gfx::get().device()->CreateBuffer(&bd, &sd, &this->mp_buffer));
		}

		void	create_buffer()
		{
			HRESULT hr;

			D3D11_BUFFER_DESC bd;
			bd.ByteWidth = sizeof(T);
			bd.StructureByteStride = 0u;
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bd.MiscFlags = 0u;

			GFX_ASSERT(PULSAR::gfx::get().device()->CreateBuffer(&bd, NULL, &this->buffer));
		}

		void	free()
		{
			if (this->mp_buffer)
			{
				ULONG ref_count = this->mp_buffer->Release();
				if (ref_count == 0)
					this->mp_buffer = NULL;
			}
		}

	public:
		const_buffer<T> &operator=(const const_buffer<T>&) = delete;
		const_buffer<T> &operator=(const_buffer<T>&&) = delete;
		const_buffer(const const_buffer<T>&) = delete;
		const_buffer(const_buffer<T>&&) = delete;
		const_buffer(UINT slot = 0u)
		{
			this->create_buffer();
			this->set_slot(slot);
		}
		const_buffer(const T &data, UINT slot = 0u)
		{
			this->create_buffer(data);
			this->set_slot(slot);
		}
		~const_buffer()
		{
			this->free();
		}

		void	update()
		{
			D3D11_MAPPED_SUBRESOURCE ms;
			GFX_ASSERT(PULSAR::gfx::get().device_context()->Map(this->mp_buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms));
			memcpy(ms.pData, this->mp_data, this->m_data_size);
			PULSAR::gfx::get().device_context()->Unmap(this->mp_buffer, 0u);
		}
		void	update(const T &data)
		{
			this->mp_data = &data;
			this->m_data_size = sizeof(data);

			D3D11_MAPPED_SUBRESOURCE ms;
			GFX_ASSERT(PULSAR::gfx::get().device_context()->Map(this->mp_buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms));
			memcpy(ms.pData, &data, sizeof(data));
			PULSAR::gfx::get().device_context()->Unmap(this->mp_buffer, 0u);
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
