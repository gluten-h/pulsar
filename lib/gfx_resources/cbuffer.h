#pragma once

#include "buffer_resource.h"
#include "exceptions/gfx_exception.h"


namespace pulsar
{
	enum class CBUFFER_TYPE
	{
		IMMUTABLE,
		DYNAMIC
	};

	template <typename T>
	class cbuffer : public pulsar::buffer_resource
	{
	protected:
		const T *mp_data = NULL;
		UINT m_slot = 0u;
		bool m_is_modified = false;

	private:
		void	create_cbuffer(const T *data, pulsar::CBUFFER_TYPE type)
		{
			this->mp_data = data;

			D3D11_BUFFER_DESC bd;
			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
			ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));

			bd.ByteWidth = sizeof(T);
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			switch (type)
			{
				case pulsar::CBUFFER_TYPE::DYNAMIC:
				{
					bd.Usage = D3D11_USAGE_DYNAMIC;
					bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
					break;
				}
				case pulsar::CBUFFER_TYPE::IMMUTABLE:
				{
					bd.Usage = D3D11_USAGE_IMMUTABLE;
					bd.CPUAccessFlags = 0u;
					break;
				}
			}
			sd.pSysMem = data;
			this->create_buffer(&bd, &sd);
		}

	protected:
		cbuffer<T> &operator=(const cbuffer<T>&) = delete;
		cbuffer<T> &operator=(cbuffer<T>&&) = delete;
		cbuffer(const cbuffer<T>&) = delete;
		cbuffer(cbuffer<T>&&) = delete;
		cbuffer() = default;
		cbuffer(const T *data, pulsar::CBUFFER_TYPE type = pulsar::CBUFFER_TYPE::DYNAMIC, UINT slot = 0u)
		{
			this->create_cbuffer(data, type);
			this->m_slot = slot;
		}
		virtual ~cbuffer() = default;

	public:
		void	set(const T *data, pulsar::CBUFFER_TYPE type = pulsar::CBUFFER_TYPE::DYNAMIC)
		{
			this->destroy_buffer();
			this->create_cbuffer(data, type);
		}

		void	ref_data(const T *data)
		{
			this->mp_data = data;
		}

		void	set_slot(UINT slot)
		{
			this->m_slot = slot;
		}

		bool	is_modified() const
		{
			return (this->m_is_modified);
		}
		void	set_modified()
		{
			this->m_is_modified = true;
		}

		void	update()
		{
			this->m_is_modified = false;

			D3D11_MAPPED_SUBRESOURCE ms;
			GFX_ASSERT(pulsar::gfx::instance().device_context()->Map(this->mp_buffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &ms));
			memcpy(ms.pData, this->mp_data, sizeof(T));
			pulsar::gfx::instance().device_context()->Unmap(this->mp_buffer, 0u);
		}
	};
}
