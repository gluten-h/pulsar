
#include "grng_deferred_buffer.h"


GRNG_TEXTURE2D				&grng_deferred_buffer::get_render_texture_texture(UINT type)
{
	return (this->rt_texture[type]);
}

GRNG_RENDER_TEXTURE			&grng_deferred_buffer::get_render_texture(UINT type)
{
	return (this->rt[type]);
}

GRNG_DEPTH_STENCIL			&grng_deferred_buffer::get_depth_stencil()
{
	return (this->ds);
}

D3D11_VIEWPORT				&grng_deferred_buffer::get_viewport()
{
	return (this->viewport);
}
