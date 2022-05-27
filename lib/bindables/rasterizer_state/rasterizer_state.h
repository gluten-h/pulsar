#pragma once

#include "bindable/bindable.h"


namespace pulsar
{
	class rasterizer_state : public pulsar::bindable
	{
	private:
		ID3D11RasterizerState *mp_rs = NULL;

	private:
		void	create_rs(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);
		void	free();

	public:
		rasterizer_state &operator=(const rasterizer_state&) = delete;
		rasterizer_state &operator=(rasterizer_state&&) = delete;
		rasterizer_state(const rasterizer_state&) = delete;
		rasterizer_state(rasterizer_state&&) = delete;
		rasterizer_state() = default;
		rasterizer_state(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);
		~rasterizer_state();

		void	set(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);
		ID3D11RasterizerState	*get();

		void	bind() const;
		void	unbind() const;
	};
}
