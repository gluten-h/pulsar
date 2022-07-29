#pragma once

#include "gfx/gfx.h"


namespace pulsar
{
	class rasterizer_state
	{
	private:
		ID3D11RasterizerState *mp_rs = NULL;

		void	create_rs(D3D11_CULL_MODE cull_mode, D3D11_FILL_MODE fill_mode);
		void	destroy_rs();

	public:
		rasterizer_state &operator=(const rasterizer_state&) = delete;
		rasterizer_state &operator=(rasterizer_state&&) = delete;
		rasterizer_state(const rasterizer_state&) = delete;
		rasterizer_state(rasterizer_state&&) = delete;
		rasterizer_state() = default;
		rasterizer_state(D3D11_CULL_MODE cull_mode, D3D11_FILL_MODE fill_mode = D3D11_FILL_SOLID);
		~rasterizer_state();

		void	set(D3D11_CULL_MODE cull_mode, D3D11_FILL_MODE fill_mode = D3D11_FILL_SOLID);

		void	bind() const;
		void	unbind() const;
	};
}
