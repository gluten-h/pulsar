
#include "depth_stencil_state.h"


void		PULSAR::DEPTH_STENCIL_STATE::copy_assign(const DEPTH_STENCIL_STATE &dss)
{
	this->ds_state = dss.ds_state;
	if (this->ds_state)
		this->ds_state->AddRef();
}


PULSAR::DEPTH_STENCIL_STATE		&PULSAR::DEPTH_STENCIL_STATE::operator=(const DEPTH_STENCIL_STATE &dss)
{
	if (this->ds_state != dss.ds_state)
		this->remove_ds_memory();
	this->copy_assign(dss);

	return (*this);
}

PULSAR::DEPTH_STENCIL_STATE::DEPTH_STENCIL_STATE(const DEPTH_STENCIL_STATE &dss) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::DEPTH_STENCIL_STATE;
	this->copy_assign(dss);
}

PULSAR::DEPTH_STENCIL_STATE::DEPTH_STENCIL_STATE(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask) : BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::DEPTH_STENCIL_STATE;
	this->set(depth_enable, depth_comp_func, depth_write_mask);
}

PULSAR::DEPTH_STENCIL_STATE::~DEPTH_STENCIL_STATE()
{
	this->remove_ds_memory();
}
