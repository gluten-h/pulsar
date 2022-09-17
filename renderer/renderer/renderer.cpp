
#include "renderer.h"


pulsar::viewport_rq		&pulsar::renderer::viewport_rq()
{
	return (this->m_viewport_rq);
}

pulsar::shadows_rq		&pulsar::renderer::shadows_rq()
{
	return (this->m_shadows_rq);
}


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

pulsar::array<pulsar::ecs::entity, pulsar::MAX_SCENE_LIGHTS_COUNT>	*pulsar::renderer::get_submitted_lights()
{
	return (this->mp_submitted_lights);
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

void	pulsar::renderer::submit_lights(pulsar::array<pulsar::ecs::entity, pulsar::MAX_SCENE_LIGHTS_COUNT> *lights)
{
	this->mp_submitted_lights = lights;
}
