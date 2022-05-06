
#include "depth_stencil_view.h"


PULSAR::depth_stencil_view::depth_stencil_view(float width, float height)
{
	this->create_ds_view(width, height);
}

PULSAR::depth_stencil_view::~depth_stencil_view()
{
	this->free();
}

void	PULSAR::depth_stencil_view::resize(UINT width, UINT height)
{
	this->set(width, height);
	this->resize_linked(width, height);
}

void	PULSAR::depth_stencil_view::clear()
{
	PULSAR::gfx::get().device_context()->ClearDepthStencilView(this->mp_ds_view, D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void	PULSAR::depth_stencil_view::bind() const{ }
void	PULSAR::depth_stencil_view::unbind() const{ }
