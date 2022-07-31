#pragma once

#include "gfx/gfx.h"
#include <array>


namespace pulsar
{
	template <size_t SIZE>
	class srv_bind_group
	{
	private:
		ID3D11ShaderResourceView *data[SIZE] = { NULL };
		UINT m_slot = 0u;

	public:
		srv_bind_group() = default;
		srv_bind_group(const std::array<ID3D11ShaderResourceView*, SIZE> &data, UINT start_slot = 0u)
		{
			this->set(data);
			this->m_slot = start_slot;
		}
		~srv_bind_group() = default;

		void	set(const std::array<ID3D11ShaderResourceView*, SIZE> &data)
		{
			int i = -1;
			while (++i < SIZE)
				this->data[i] = data[i];
		}

		void	set_slot(UINT start_slot)
		{
			this->m_slot = start_slot;
		}

		void	bind() const
		{
			pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, SIZE, this->data);
		}

		void	unbind() const
		{
			ID3D11ShaderResourceView *null[SIZE] = { NULL };
			pulsar::gfx::instance().device_context()->PSSetShaderResources(this->m_slot, SIZE, null);
		}
	};
}
