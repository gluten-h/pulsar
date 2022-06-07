
#include "node_rotation.h"
#include "transform/transform_component.h"


pulsar::node_rotation::node_rotation(pulsar::node *node, float speed, const XMFLOAT3 &rotation_axis) : pulsar::script(node)
{
	this->m_speed = speed;
	this->m_rot_axis = rotation_axis;
}

void	pulsar::node_rotation::execute(float delta_time)
{
	pulsar::transform &transform = this->mp_node->get_component<pulsar::transform_component>().transform;
	XMFLOAT3 rotation = transform.get_rotation();

	float rot_value = this->m_speed * delta_time;
	rotation = XMFLOAT3(rotation.x + rot_value * this->m_rot_axis.x, rotation.y + rot_value * this->m_rot_axis.y, rotation.z + rot_value * this->m_rot_axis.z);
	transform.set_rotation(rotation);
}
