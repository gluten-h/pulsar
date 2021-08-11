#pragma once

#include "grng_bindable.h"
#include "grng_bindable_entity.h"


class grng_depth_stencil_state : public GRNG_BINDABLE
{
private:
	ID3D11DepthStencilState		*ds_state = NULL;


	void		set_ds_memory(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask);
	void		remove_ds_memory();

	void		copy_assign(const grng_depth_stencil_state &dss);

protected:
	void		remove_from_entities() override
	{
		for (auto &it : this->entities)
			it->_remove_bindable_ignore_entity(this);
		this->entities.clear();
	}

public:
	using GRNG_BINDABLE::bind;

public:
	grng_depth_stencil_state		&operator=(const grng_depth_stencil_state &dss);
	grng_depth_stencil_state(const grng_depth_stencil_state &dss);
	grng_depth_stencil_state(BOOL depth_enable = TRUE, D3D11_COMPARISON_FUNC depth_comp_func = D3D11_COMPARISON_LESS, D3D11_DEPTH_WRITE_MASK depth_write_mask = D3D11_DEPTH_WRITE_MASK_ALL);
	~grng_depth_stencil_state();

	void						set(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask);
	ID3D11DepthStencilState		*get_state();

	static grng_depth_stencil_state		*create();

	void		bind() const override
	{
		this->device_context->OMSetDepthStencilState(this->ds_state, 1u);
		GRNG_BINDABLE::add_unbind(*this);
	}

	void		unbind() const override
	{
		this->device_context->OMSetDepthStencilState(NULL, 1u);
	}
};

using GRNG_DEPTH_STENCIL_STATE = grng_depth_stencil_state;
using GRNG_DS_STATE = grng_depth_stencil_state;
