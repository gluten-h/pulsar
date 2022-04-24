
#include "viewport.h"


PULSAR::viewport::viewport(float width, float height, float min_depth, float max_depth)
{
	this->create_viewport(width, height, min_depth, max_depth);
}

void	PULSAR::viewport::bind() const
{
	PULSAR::gfx::get().device_context()->RSSetViewports(1u, &this->m_viewport);
}

void	PULSAR::viewport::unbind() const
{
	static D3D11_VIEWPORT null_ptr[1] = { NULL };
	PULSAR::gfx::get().device_context()->RSSetViewports(1u, null_ptr);
}
