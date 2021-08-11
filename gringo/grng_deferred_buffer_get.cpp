
#include "grng_deferred_buffer.h"


GRNG_TEXTURE2D				&grng_deferred_buffer::get_render_texture_texture(UINT type)
{
	return (this->rt_texture[type]);
}

GRNG_RENDER_TEXTURE			&grng_deferred_buffer::get_render_texture(UINT type)
{
	return (this->rt[type]);
}

GRNG_RENDER_TEXTURE			&grng_deferred_buffer::get_hdr_buffer()
{
	return (this->rt_hdr);
}

GRNG_DS_VIEW				&grng_deferred_buffer::get_ds_view()
{
	return (this->ds_view);
}

GRNG_DS_STATE				&grng_deferred_buffer::get_ds_state()
{
	return (this->ds_state);
}

GRNG_VIEWPORT				&grng_deferred_buffer::get_viewport()
{
	return (this->viewport);
}
