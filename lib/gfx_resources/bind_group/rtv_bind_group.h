#pragma once

#include "gfx/gfx.h"
#include <array>


namespace pulsar
{
	template <size_t SIZE>
	class rtv_bind_group
	{
	private:
		ID3D11RenderTargetView *data[SIZE] = { NULL };

	public:
		rtv_bind_group() = default;
		rtv_bind_group(const std::array<ID3D11RenderTargetView*, SIZE> &data)
		{
			this->set(data);
		}
		~rtv_bind_group() = default;

		void	set(const std::array<ID3D11RenderTargetView*, SIZE> &data)
		{
			int i = -1;
			while (++i < SIZE)
				this->data[i] = data[i];
		}

		void	bind(ID3D11DepthStencilView *dsv = NULL) const
		{
			pulsar::gfx::instance().device_context()->OMSetRenderTargets(SIZE, this->data, dsv);
		}

		void	unbind() const
		{
			ID3D11RenderTargetView *null[SIZE] = { NULL };
			pulsar::gfx::instance().device_context()->OMSetRenderTargets(SIZE, null, NULL);
		}
	};
}
