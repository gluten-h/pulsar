#pragma once

#include "script/script.h"
#include "utils/math.h"


namespace pulsar
{
	class node;

	class node_rotation_orbit : public pulsar::script
	{
	private:
		pulsar::node *mp_node = NULL;

		float m_speed;
		XMFLOAT3 m_rot_center;
		XMFLOAT3 m_rot_axis;

	public:
		node_rotation_orbit &operator=(const node_rotation_orbit&) = delete;
		node_rotation_orbit &operator=(node_rotation_orbit&&) = delete;
		node_rotation_orbit(const node_rotation_orbit&) = delete;
		node_rotation_orbit(node_rotation_orbit&&) = delete;
		node_rotation_orbit() = delete;
		node_rotation_orbit(pulsar::node *node, float speed, const XMFLOAT3 &rotation_center, const XMFLOAT3 &rotation_axis = XMFLOAT3(0.0f, 1.0f, 0.0f));
		~node_rotation_orbit() = default;

		void	execute(float delta_time);
	};
}
