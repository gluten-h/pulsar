
#include "grng_viewport.h"


void			grng_viewport::set_viewport_memory(float width, float height, float min_depth, float max_depth)
{
	this->viewport.TopLeftX = 0.0f;
	this->viewport.TopLeftY = 0.0f;
	this->viewport.Width = width;
	this->viewport.Height = height;
	this->viewport.MinDepth = min_depth;
	this->viewport.MaxDepth = max_depth;
}

void			grng_viewport::set(float width, float height, float min_depth, float max_depth)
{
	this->set_viewport_memory(width, height, min_depth, max_depth);
}

D3D11_VIEWPORT	&grng_viewport::get()
{
	return (this->viewport);
}


grng_viewport	*grng_viewport::create()
{
	grng_viewport *viewport = new grng_viewport;
	viewport->id = GRNG_BM.add(viewport);
	if (viewport->id == -1)
	{
		delete viewport;
		return (NULL);
	}
	viewport->is_alloc = true;

	return (viewport);
}
