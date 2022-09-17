#pragma once

#include "script/script.h"
#include "node/node.h"
#include "utils/math.h"


namespace pulsar
{
	class node_rotation : public pulsar::script
	{
	private:
		pulsar::node *mp_node = NULL;
		float m_speed;
		XMFLOAT3 m_rot_axis;

	public:
		node_rotation &operator=(const node_rotation&) = delete;
		node_rotation &operator=(node_rotation&&) = delete;
		node_rotation(const node_rotation&) = delete;
		node_rotation(node_rotation&&) = delete;
		node_rotation() = delete;
		node_rotation(pulsar::node *node, float speed, const XMFLOAT3 &rotation_axis = XMFLOAT3(1.0f, 1.0f, 1.0f));
		~node_rotation() = default;

		void	execute(float delta_time) override;
	};
}
