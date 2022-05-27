
#include "scene.h"
#include "node/node.h"
#include "camera/camera_component.h"

#include "systems/camera_system.h"
#include "systems/render_system.h"
#include "systems/light_system.h"


pulsar::scene *pulsar::scene::mp_active_scene = NULL;


pulsar::scene::scene()
{
	this->register_system<pulsar::camera_system>(&this->m_registry);
	this->register_system<pulsar::render_system>(&this->m_registry);
	this->register_system<pulsar::light_system>(&this->m_registry);
}

pulsar::scene::~scene()
{
	for (pulsar::ecs::system *sys : this->m_systems)
		delete sys;
}

pulsar::ecs::registry	&pulsar::scene::registry()
{
	return (this->m_registry);
}

void	pulsar::scene::set_active_scene(pulsar::scene *scene)
{
	pulsar::scene::mp_active_scene = scene;
}

pulsar::scene	*pulsar::scene::get_active_scene()
{
	return (pulsar::scene::mp_active_scene);
}

void	pulsar::scene::set_main_camera(pulsar::node *camera)
{
	this->mp_main_camera = camera;
}

pulsar::node	*pulsar::scene::get_main_camera()
{
	return (this->mp_main_camera);
}

pulsar::skybox_material		&pulsar::scene::skybox_material()
{
	return (this->m_skybox_material);
}

void	pulsar::scene::update(float delta_time)
{
	for (pulsar::ecs::system *sys : this->m_systems)
		sys->execute(delta_time);
}
