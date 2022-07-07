
#include "scene.h"
#include "node/node.h"

#include "metadata/metadata_component.h"
#include "camera/camera_component.h"

#include "systems/camera_system.h"
#include "systems/viewport_render_system.h"
#include "systems/light_system.h"
#include "systems/script_system.h"


pulsar::scene *pulsar::scene::mp_active_scene = NULL;


pulsar::scene::scene()
{
	this->m_registry.on_construct<pulsar::metadata_component>().connect<entt::invoke<&pulsar::metadata_component::on_construct>>();
	this->m_registry.on_construct<pulsar::camera_component>().connect<entt::invoke<&pulsar::camera_component::on_construct>>();

	this->register_system<pulsar::camera_system>();
	this->register_system<pulsar::viewport_render_system>();
	this->register_system<pulsar::light_system>();
	this->register_system<pulsar::script_system>();
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
	if (!camera || !camera->has_component<pulsar::camera_component>())
		return;

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
		sys->execute(this->m_registry, delta_time);
}
