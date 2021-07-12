
#include "grng_depth_stencil_view.h"


void					grng_depth_stencil_view::copy_assign(const grng_depth_stencil_view &dsv)
{
	this->ds_texture = dsv.ds_texture;
	this->ds_view = dsv.ds_view;

	if (this->ds_texture)
		this->ds_texture->AddRef();
	if (this->ds_view)
		this->ds_view->AddRef();
}


grng_depth_stencil_view		&grng_depth_stencil_view::operator=(const grng_depth_stencil_view &dsv)
{
	if (this->ds_texture != dsv.ds_texture)
		this->remove_ds_texture_memory();
	if (this->ds_view != dsv.ds_view)
		this->remove_ds_view_memory();

	this->copy_assign(dsv);

	return (*this);
}

grng_depth_stencil_view::grng_depth_stencil_view(const grng_depth_stencil_view &dsv) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::DEPTH_STENCIL_VIEW;
	this->copy_assign(dsv);
}

grng_depth_stencil_view::grng_depth_stencil_view() : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::DEPTH_STENCIL_VIEW;
}

grng_depth_stencil_view::grng_depth_stencil_view(float width, float height) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::DEPTH_STENCIL_VIEW;
	this->set_ds_memory(width, height);
}

grng_depth_stencil_view::~grng_depth_stencil_view()
{
	this->remove_ds_memory();
}
