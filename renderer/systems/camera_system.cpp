
#include "camera_system.h"
#include "config/config.h"
#include "renderer/renderer.h"
#include "scene/scene.h"
#include "node/node.h"
#include "transform/transform_component.h"
#include "camera/camera_component.h"


pulsar::camera_system::camera_system()
{
	this->m_vert_camera_cbuffer.set(&this->m_vert_camera, pulsar::CBUFFER_TYPE::DYNAMIC);
	this->m_frag_camera_cbuffer.set(&this->m_frag_camera, pulsar::CBUFFER_TYPE::DYNAMIC);
}

void	pulsar::camera_system::execute(pulsar::ecs::registry &registry, float delta_time)
{
	pulsar::node *main_camera = pulsar::scene::get_active_scene()->get_main_camera();
	if (!main_camera)
		return;

	pulsar::transform &transform = main_camera->get_component<pulsar::transform_component>().transform;
	pulsar::camera_component &camera = main_camera->get_component<pulsar::camera_component>();

	const XMFLOAT4X4 &mat_f4x4 = transform.get_matrix();
	const XMFLOAT3 &pos_f3 = transform.get_position();
	const XMFLOAT3 forward_f3 = transform.forward();
	const XMFLOAT3 up_f3 = transform.up();
	const XMFLOAT4X4 &cam_proj_f4x4 = camera.camera->projection();

	XMMATRIX mat = XMLoadFloat4x4(&mat_f4x4);
	XMVECTOR pos = XMLoadFloat3(&pos_f3);
	XMVECTOR forward = XMLoadFloat3(&forward_f3);
	XMVECTOR up = XMLoadFloat3(&up_f3);

	XMMATRIX view = XMMatrixTranspose(XMMatrixLookToLH(pos, forward, up));
	XMMATRIX proj = XMMatrixTranspose(XMLoadFloat4x4(&cam_proj_f4x4));

	XMStoreFloat4x4(&this->m_vert_camera.view, view);
	XMStoreFloat4x4(&this->m_vert_camera.proj, proj);

	this->m_frag_camera.pos = pos_f3;
	this->m_frag_camera.gamma = camera.gamma;
	this->m_frag_camera.dir = forward_f3;
	this->m_frag_camera.exposure = camera.exposure;

	this->m_vert_camera_cbuffer.update();
	this->m_frag_camera_cbuffer.update();

	pulsar::renderer::instance().submit_main_camera_viewport(&camera.camera->viewport());
	pulsar::renderer::instance().submit_vert_camera_cbuffer(&this->m_vert_camera_cbuffer);
	pulsar::renderer::instance().submit_frag_camera_cbuffer(&this->m_frag_camera_cbuffer);
}
