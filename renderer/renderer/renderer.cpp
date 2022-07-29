
#include "renderer.h"


pulsar::viewport	*pulsar::renderer::get_main_camera_viewport()
{
	return (this->mp_main_camera_viewport);
}

pulsar::vert_cbuffer<pulsar::vert_camera>	*pulsar::renderer::get_vert_camera_cbuffer()
{
	return (this->mp_vert_camera_cbuffer);
}

pulsar::frag_cbuffer<pulsar::frag_camera>	*pulsar::renderer::get_frag_camera_cbuffer()
{
	return (this->mp_frag_camera_cbuffer);
}

pulsar::frag_cbuffer<pulsar::deferred_frag_lights>		*pulsar::renderer::get_deferred_frag_lights_cbuffer()
{
	return (this->mp_deferred_frag_lights_cbuffer);
}


void	pulsar::renderer::submit_main_camera_viewport(pulsar::viewport *viewport)
{
	this->mp_main_camera_viewport = viewport;
}

void	pulsar::renderer::submit_vert_camera_cbuffer(pulsar::vert_cbuffer<pulsar::vert_camera> *cbuffer)
{
	this->mp_vert_camera_cbuffer = cbuffer;
}

void	pulsar::renderer::submit_frag_camera_cbuffer(pulsar::frag_cbuffer<pulsar::frag_camera> *cbuffer)
{
	this->mp_frag_camera_cbuffer = cbuffer;
}

void	pulsar::renderer::submit_deferred_frag_lights_cbuffer(pulsar::frag_cbuffer<pulsar::deferred_frag_lights> *cbuffer)
{
	this->mp_deferred_frag_lights_cbuffer = cbuffer;
}
