
#include "node_rotation_orbit.h"
#include "node/node.h"
#include "transform/transform_component.h"
#include "input/pulsar_input.h"


pulsar::node_rotation_orbit::node_rotation_orbit(pulsar::node *node, float speed, const XMFLOAT3 &rotation_center, const XMFLOAT3 &rotation_axis)
{
	this->mp_node = node;
	this->m_speed = speed;
	this->m_rot_center = rotation_center;
	this->m_rot_axis = rotation_axis;
}

void	pulsar::node_rotation_orbit::execute(float delta_time)
{
	pulsar::transform &transform = this->mp_node->get_component<pulsar::transform_component>().transform;
	XMFLOAT3 pos = transform.get_position();

	static float angle = 0.0f;

	angle += this->m_speed * delta_time;
	pos.x = cosf(angle) * 3.0f;
	pos.z = sinf(angle) * 3.0f;

	transform.set_position(pos);
}
