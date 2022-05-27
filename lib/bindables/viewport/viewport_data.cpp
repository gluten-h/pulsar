
#include "viewport.h"


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

D3D11_VIEWPORT	&pulsar::viewport::get()
{
	return (this->m_viewport);
}
