
#include "renderer.h"


pulsar::vert_const_buffer<pulsar::vert_camera>	*pulsar::renderer::get_vert_camera_cbuffer()
{
	return (this->mp_vert_camera_cbuffer);
}

pulsar::frag_const_buffer<pulsar::frag_camera>	*pulsar::renderer::get_frag_camera_cbuffer()
{
	return (this->mp_frag_camera_cbuffer);
}

pulsar::frag_const_buffer<pulsar::deferred_frag_lights>		*pulsar::renderer::get_deferred_frag_lights_cbuffer()
{
	return (this->mp_deferred_frag_lights_cbuffer);
}

void	pulsar::renderer::submit_vert_camera_cbuffer(pulsar::vert_const_buffer<pulsar::vert_camera> *cbuffer)
{
	this->mp_vert_camera_cbuffer = cbuffer;
}

void	pulsar::renderer::submit_frag_camera_cbuffer(pulsar::frag_const_buffer<pulsar::frag_camera> *cbuffer)
{
	this->mp_frag_camera_cbuffer = cbuffer;
}

void	pulsar::renderer::submit_deferred_frag_lights_cbuffer(pulsar::frag_const_buffer<pulsar::deferred_frag_lights> *cbuffer)
{
	this->mp_deferred_frag_lights_cbuffer = cbuffer;
}
