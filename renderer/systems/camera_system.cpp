
#include "camera_system.h"
#include "config/config.h"
#include "renderer/renderer.h"
#include "scene/scene.h"
#include "node/node.h"
#include "transform/transform_component.h"
#include "camera/camera_component.h"


pulsar::camera_system::camera_system(pulsar::ecs::registry *registry) : pulsar::ecs::system(registry)
{
	this->mp_vert_camera_cbuffer = new vert_camera_cbuffer(this->m_vert_camera, 0u);
	this->mp_frag_camera_cbuffer = new frag_camera_cbuffer(this->m_frag_camera, 0u);
}

pulsar::camera_system::~camera_system()
{
	delete this->mp_vert_camera_cbuffer;
	delete this->mp_frag_camera_cbuffer;
}

void	pulsar::camera_system::execute(float delta_time)
{
	pulsar::node *main_camera = pulsar::scene::get_active_scene()->get_main_camera();
	if (!main_camera || !main_camera->has_component<pulsar::camera_component>())
		return;

	pulsar::transform_component &transform = main_camera->get_component<pulsar::transform_component>();
	pulsar::camera_component &camera = main_camera->get_component<pulsar::camera_component>();

	this->m_vert_camera.view = XMMatrixTranspose(transform.transform.get_matrix());
	this->m_vert_camera.proj = XMMatrixTranspose(camera.camera->get_projection());

	this->m_frag_camera.pos = transform.transform.get_position();
	this->m_frag_camera.gamma = camera.gamma;
	this->m_frag_camera.dir = transform.transform.forward();
	this->m_frag_camera.exposure = camera.exposure;

	this->mp_vert_camera_cbuffer->update();
	this->mp_frag_camera_cbuffer->update();

	pulsar::renderer::instance().submit_vert_camera_cbuffer(this->mp_vert_camera_cbuffer);
	pulsar::renderer::instance().submit_frag_camera_cbuffer(this->mp_frag_camera_cbuffer);
}
