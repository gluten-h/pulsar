#pragma once

#include "gfx/gfx.h"
#include <array>


namespace pulsar
{
	template <size_t SIZE>
	class cbuffer_bind_group
	{
	protected:
		ID3D11Buffer *data[SIZE] = { NULL };
		UINT m_slot = 0u;

		cbuffer_bind_group() = default;
		cbuffer_bind_group(const std::array<ID3D11Buffer*, SIZE> &data, UINT start_slot = 0u)
		{
			this->set(data);
			this->m_slot = start_slot;
		}
		~cbuffer_bind_group() = default;

	public:
		void	set(const std::array<ID3D11Buffer*, SIZE> &data)
		{
			int i = -1;
			while (++i < SIZE)
				this->data[i] = data[i];
		}

		void	set_slot(UINT start_slot)
		{
			this->m_slot = start_slot;
		}
	};
}
