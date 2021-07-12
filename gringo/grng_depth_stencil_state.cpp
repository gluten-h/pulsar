
#include "grng_depth_stencil_state.h"


void		grng_depth_stencil_state::copy_assign(const grng_depth_stencil_state &dss)
{
	this->ds_state = dss.ds_state;
	if (this->ds_state)
		this->ds_state->AddRef();
}


grng_depth_stencil_state		&grng_depth_stencil_state::operator=(const grng_depth_stencil_state &dss)
{
	if (this->ds_state != dss.ds_state)
		this->remove_ds_memory();
	this->copy_assign(dss);

	return (*this);
}

grng_depth_stencil_state::grng_depth_stencil_state(const grng_depth_stencil_state &dss) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::DEPTH_STENCIL_STATE;
	this->copy_assign(dss);
}

grng_depth_stencil_state::grng_depth_stencil_state(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::DEPTH_STENCIL_STATE;
	this->set(depth_enable, depth_comp_func, depth_write_mask);
}

grng_depth_stencil_state::~grng_depth_stencil_state()
{
	this->remove_ds_memory();
}
