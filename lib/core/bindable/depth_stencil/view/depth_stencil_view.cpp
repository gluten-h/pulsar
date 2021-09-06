
#include "depth_stencil_view.h"


void	PULSAR::DEPTH_STENCIL_VIEW::copy_assign(const DEPTH_STENCIL_VIEW &dsv)
{
	this->ds_texture = dsv.ds_texture;
	this->ds_view = dsv.ds_view;

	if (this->ds_texture)
		this->ds_texture->AddRef();
	if (this->ds_view)
		this->ds_view->AddRef();
}


PULSAR::DEPTH_STENCIL_VIEW		&PULSAR::DEPTH_STENCIL_VIEW::operator=(const DEPTH_STENCIL_VIEW &dsv)
{
	if (this->ds_texture != dsv.ds_texture)
		this->remove_ds_texture_memory();
	if (this->ds_view != dsv.ds_view)
		this->remove_ds_view_memory();

	this->copy_assign(dsv);

	return (*this);
}

PULSAR::DEPTH_STENCIL_VIEW::DEPTH_STENCIL_VIEW(const DEPTH_STENCIL_VIEW &dsv) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::DEPTH_STENCIL_VIEW;
	this->copy_assign(dsv);
}

PULSAR::DEPTH_STENCIL_VIEW::DEPTH_STENCIL_VIEW() : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::DEPTH_STENCIL_VIEW;
}

PULSAR::DEPTH_STENCIL_VIEW::DEPTH_STENCIL_VIEW(float width, float height) : PULSAR::BINDABLE()
{
	this->type = PULSAR::BINDABLE_TYPE::DEPTH_STENCIL_VIEW;
	this->set_ds_memory(width, height);
}

PULSAR::DEPTH_STENCIL_VIEW::~DEPTH_STENCIL_VIEW()
{
	this->remove_ds_memory();
}
