
#include "grng_depth_stencil.h"


void					grng_depth_stencil::copy_assign(const grng_depth_stencil &ds)
{
	this->ds_texture = ds.ds_texture;
	this->ds_state = ds.ds_state;
	this->ds_view = ds.ds_view;

	if (this->ds_texture)
		this->ds_texture->AddRef();
	if (this->ds_state)
		this->ds_state->AddRef();
	if (this->ds_view)
		this->ds_view->AddRef();
}


grng_depth_stencil		&grng_depth_stencil::operator=(const grng_depth_stencil &ds)
{
	if (this->ds_texture != ds.ds_texture)
		this->remove_ds_texture_memory();
	if (this->ds_state != ds.ds_state)
		this->remove_ds_state_memory();
	if (this->ds_view != ds.ds_view)
		this->remove_ds_view_memory();

	this->copy_assign(ds);

	return (*this);
}

grng_depth_stencil::grng_depth_stencil(const grng_depth_stencil &ds) : GRNG_BINDABLE()
{
	this->copy_assign(ds);
}

grng_depth_stencil::grng_depth_stencil() : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::DEPTH_STENCIL;
}

grng_depth_stencil::grng_depth_stencil(float width, float height, D3D11_COMPARISON_FUNC comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::DEPTH_STENCIL;

	this->set_ds_memory(width, height, comp_func, depth_write_mask);
}

grng_depth_stencil::~grng_depth_stencil()
{
	this->remove_ds_memory();
}
