#pragma once

#include "bindable/bindable.h"


namespace PULSAR
{
	class depth_stencil_state : public PULSAR::bindable
	{
	private:
		ID3D11DepthStencilState *mp_ds_state = NULL;

	private:
		void	create_ds_state(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask);
		void	free();

	public:
		depth_stencil_state &operator=(const depth_stencil_state &) = delete;
		depth_stencil_state &operator=(depth_stencil_state&&) = delete;
		depth_stencil_state(const depth_stencil_state &dss) = delete;
		depth_stencil_state(depth_stencil_state&&) = delete;
		depth_stencil_state() = default;
		depth_stencil_state(BOOL depth_enable = TRUE, D3D11_COMPARISON_FUNC depth_comp_func = D3D11_COMPARISON_LESS, D3D11_DEPTH_WRITE_MASK depth_write_mask = D3D11_DEPTH_WRITE_MASK_ALL);
		~depth_stencil_state();

		void	set(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask);
		ID3D11DepthStencilState		*get();

		void	bind() const override;
		void	unbind() const override;
	};

	using ds_state = depth_stencil_state;
}
