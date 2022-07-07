
#include "camera_system.h"
#include "config/config.h"
#include "renderer/renderer.h"
#include "scene/scene.h"
#include "node/node.h"
#include "transform/transform_component.h"
#include "camera/camera_component.h"


pulsar::camera_system::camera_system()
{
	this->mp_vert_camera_cbuffer = new vert_camera_cbuffer(this->m_vert_camera, 0u);
	this->mp_frag_camera_cbuffer = new frag_camera_cbuffer(this->m_frag_camera, 0u);
}

pulsar::camera_system::~camera_system()
{
	delete this->mp_vert_camera_cbuffer;
	delete this->mp_frag_camera_cbuffer;
}

void	pulsar::camera_system::execute(pulsar::ecs::registry &registry, float delta_time)
{
	pulsar::node *main_camera = pulsar::scene::get_active_scene()->get_main_camera();
	if (!main_camera)
		return;

	pulsar::transform &transform = main_camera->get_component<pulsar::transform_component>().transform;
	pulsar::camera_component &camera = main_camera->get_component<pulsar::camera_component>();

	const XMMATRIX &transform_mat = transform.get_matrix();
	XMVECTOR forward_vec = XMVector3NormalizeEst(transform_mat.r[2]);
	XMVECTOR up_vec = XMVector3NormalizeEst(transform_mat.r[1]);

	this->m_vert_camera.view = XMMatrixTranspose(XMMatrixLookToLH(transform_mat.r[3], forward_vec, up_vec));
	this->m_vert_camera.proj = XMMatrixTranspose(camera.camera->get_projection());

	this->m_frag_camera.pos = transform.get_position();
	this->m_frag_camera.gamma = camera.gamma;
	this->m_frag_camera.dir = transform.forward();
	this->m_frag_camera.exposure = camera.exposure;

	this->mp_vert_camera_cbuffer->update();
	this->mp_frag_camera_cbuffer->update();

	pulsar::renderer::instance().submit_main_camera_viewport(&camera.camera->viewport());
	pulsar::renderer::instance().submit_vert_camera_cbuffer(this->mp_vert_camera_cbuffer);
	pulsar::renderer::instance().submit_frag_camera_cbuffer(this->mp_frag_camera_cbuffer);
}
