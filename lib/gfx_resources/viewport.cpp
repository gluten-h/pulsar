
#include "viewport.h"


pulsar::viewport::viewport(UINT width, UINT height, float min_depth, float max_depth)
{
	this->create_viewport(width, height, min_depth, max_depth);
}

void	pulsar::viewport::create_viewport(UINT width, UINT height, float min_depth, float max_depth)
{
	this->m_viewport.TopLeftX = 0.0f;
	this->m_viewport.TopLeftY = 0.0f;
	this->m_viewport.Width = width;
	this->m_viewport.Height = height;
	this->m_viewport.MinDepth = min_depth;
	this->m_viewport.MaxDepth = max_depth;
}

void	pulsar::viewport::set(UINT width, UINT height, float min_depth, float max_depth)
{
	this->create_viewport(width, height, min_depth, max_depth);
}

XMUINT2		pulsar::viewport::size() const
{
	return (XMUINT2{ (UINT)this->m_viewport.Width, (UINT)this->m_viewport.Height });
}

void	pulsar::viewport::resize_resource(UINT width, UINT height)
{
	this->m_viewport.Width = width;
	this->m_viewport.Height = height;
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
