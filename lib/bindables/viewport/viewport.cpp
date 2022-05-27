
#include "viewport.h"


pulsar::viewport::viewport(UINT width, UINT height, float min_depth, float max_depth)
{
	this->create_viewport(width, height, min_depth, max_depth);
}

void	pulsar::viewport::resize(UINT width, UINT height)
{
	this->m_viewport.Width = width;
	this->m_viewport.Height = height;

	this->resize_linked(width, height);
}

void	pulsar::viewport::clear()
{

}

void	pulsar::viewport::bind() const
{
	pulsar::gfx::instance().device_context()->RSSetViewports(1u, &this->m_viewport);
}

void	pulsar::viewport::unbind() const
{
	D3D11_VIEWPORT null_ptr[1] = { NULL };
	pulsar::gfx::instance().device_context()->RSSetViewports(1u, null_ptr);
}
