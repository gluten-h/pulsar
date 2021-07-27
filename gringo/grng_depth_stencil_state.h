#pragma once

#include "grng_bindable.h"


class grng_depth_stencil_state : public GRNG_BINDABLE
{
private:
	friend class grng_manager_ptr;

private:
	ID3D11DepthStencilState		*ds_state = NULL;


	void		set_ds_memory(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask);
	void		remove_ds_memory();

	void		copy_assign(const grng_depth_stencil_state &dss);

	static GRNG_BINDABLE		*create_manager_ptr();

public:
	grng_depth_stencil_state		&operator=(const grng_depth_stencil_state &dss);
	grng_depth_stencil_state(const grng_depth_stencil_state &dss);
	grng_depth_stencil_state(BOOL depth_enable = TRUE, D3D11_COMPARISON_FUNC depth_comp_func = D3D11_COMPARISON_LESS, D3D11_DEPTH_WRITE_MASK depth_write_mask = D3D11_DEPTH_WRITE_MASK_ALL);
	~grng_depth_stencil_state();

	void						set(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask);
	ID3D11DepthStencilState		*get_state();

	void		bind() const override
	{
		this->device_context->OMSetDepthStencilState(this->ds_state, 1u);
	}
};

using GRNG_DEPTH_STENCIL_STATE = grng_depth_stencil_state;
using GRNG_DS_STATE = grng_depth_stencil_state;
