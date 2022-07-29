#pragma once

#include "gfx/gfx.h"


namespace pulsar
{
	class depth_stencil_state
	{
	private:
		ID3D11DepthStencilState *mp_dss = NULL;

		void	create_dss(BOOL depth_enable, D3D11_COMPARISON_FUNC comp_func, D3D11_DEPTH_WRITE_MASK write_mask);
		void	destroy_dss();

	public:
		depth_stencil_state &operator=(const depth_stencil_state&) = delete;
		depth_stencil_state &operator=(depth_stencil_state&&) = delete;
		depth_stencil_state(const depth_stencil_state &dss) = delete;
		depth_stencil_state(depth_stencil_state&&) = delete;
		depth_stencil_state() = delete;
		depth_stencil_state(BOOL depth_enable = TRUE, D3D11_COMPARISON_FUNC comp_func = D3D11_COMPARISON_LESS, D3D11_DEPTH_WRITE_MASK write_mask = D3D11_DEPTH_WRITE_MASK_ALL);
		~depth_stencil_state();

		void	set(BOOL depth_enable = TRUE, D3D11_COMPARISON_FUNC comp_func = D3D11_COMPARISON_LESS, D3D11_DEPTH_WRITE_MASK write_mask = D3D11_DEPTH_WRITE_MASK_ALL);
		ID3D11DepthStencilState		*dss();

		void	bind() const;
		void	unbind() const;
	};
}
