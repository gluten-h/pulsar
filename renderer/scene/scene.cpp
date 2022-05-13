
#include "scene.h"


PULSAR::scene *PULSAR::scene::mp_active_scene = NULL;


void	PULSAR::scene::set_active_scene(PULSAR::scene *scene)
{
	PULSAR::scene::mp_active_scene = scene;
}

PULSAR::scene	*PULSAR::scene::get_active_scene()
{
	return (PULSAR::scene::mp_active_scene);
}

PULSAR::node	*PULSAR::scene::get_main_camera()
{
	return (this->mp_main_camera);
}

void	PULSAR::scene::set_main_camera(PULSAR::node *camera)
{
	this->mp_main_camera = camera;
}

const PULSAR::ecs::registry		&PULSAR::scene::registry() const
{
	return (this->m_registry);
}
