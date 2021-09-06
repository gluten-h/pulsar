
#include "viewport.h"


void		PULSAR::VIEWPORT::set_viewport_memory(float width, float height, float min_depth, float max_depth)
{
	this->viewport.TopLeftX = 0.0f;
	this->viewport.TopLeftY = 0.0f;
	this->viewport.Width = width;
	this->viewport.Height = height;
	this->viewport.MinDepth = min_depth;
	this->viewport.MaxDepth = max_depth;
}

void		PULSAR::VIEWPORT::set(float width, float height, float min_depth, float max_depth)
{
	this->set_viewport_memory(width, height, min_depth, max_depth);
}

D3D11_VIEWPORT		&PULSAR::VIEWPORT::get()
{
	return (this->viewport);
}


PULSAR::VIEWPORT	*PULSAR::VIEWPORT::create()
{
	return ((PULSAR::VIEWPORT*)PULSAR::BINDABLE::add_to_manager(new PULSAR::VIEWPORT));
}
