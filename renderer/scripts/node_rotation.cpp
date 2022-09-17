
#include "node_rotation.h"
#include "transform/transform_component.h"


pulsar::node_rotation::node_rotation(pulsar::node *node, float speed, const XMFLOAT3 &rotation_axis)
{
	this->mp_node = node;
	this->m_speed = speed;
	this->m_rot_axis = rotation_axis;
}

void	pulsar::node_rotation::execute(float delta_time)
{
	pulsar::transform &transform = this->mp_node->get_component<pulsar::transform_component>().transform;
	XMFLOAT4 rot_f4 = transform.get_rotation();
	XMVECTOR rot = XMLoadFloat4(&rot_f4);

	float rot_value = this->m_speed * delta_time;
	rot = XMQuaternionMultiply(rot, XMQuaternionRotationAxis(XMLoadFloat3(&this->m_rot_axis), rot_value));

	XMStoreFloat4(&rot_f4, rot);
	transform.set_rotation(rot_f4);
}
