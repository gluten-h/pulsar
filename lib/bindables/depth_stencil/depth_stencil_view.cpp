
#include "depth_stencil_view.h"


pulsar::depth_stencil_view::depth_stencil_view(UINT width, UINT height)
{
	this->create_ds_view(width, height);
}

pulsar::depth_stencil_view::~depth_stencil_view()
{
	this->free();
}

void	pulsar::depth_stencil_view::resize(UINT width, UINT height)
{
	this->set(width, height);
	this->resize_linked(width, height);
}

void	pulsar::depth_stencil_view::clear()
{
	pulsar::gfx::instance().device_context()->ClearDepthStencilView(this->mp_ds_view, D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void	pulsar::depth_stencil_view::bind() const{ }
void	pulsar::depth_stencil_view::unbind() const{ }
