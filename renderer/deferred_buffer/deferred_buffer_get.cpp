
#include "deferred_buffer.h"


PULSAR::TEXTURE2D		&PULSAR::DEFERRED_BUFFER::get_render_texture_texture(UINT type)
{
	return (this->rt_texture[type]);
}

PULSAR::RENDER_TEXTURE		&PULSAR::DEFERRED_BUFFER::get_render_texture(UINT type)
{
	return (this->rt[type]);
}

PULSAR::RENDER_TEXTURE		&PULSAR::DEFERRED_BUFFER::get_hdr_buffer()
{
	return (this->rt_hdr);
}

PULSAR::DS_VIEW		&PULSAR::DEFERRED_BUFFER::get_ds_view()
{
	return (this->ds_view);
}

PULSAR::DS_STATE		&PULSAR::DEFERRED_BUFFER::get_ds_state()
{
	return (this->ds_state);
}

PULSAR::VIEWPORT		&PULSAR::DEFERRED_BUFFER::get_viewport()
{
	return (this->viewport);
}
