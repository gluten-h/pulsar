#pragma once

#include "script/script.h"
#include "utils/math.h"


namespace pulsar
{
	class node;

	class camera_controller : public pulsar::script
	{
	private:
		pulsar::node *mp_node = NULL;

		float m_movement_speed = 0.0f;
		float m_acc_speed = 0.0f;
		float m_lift_speed = 0.0f;
		float m_rotation_speed = 0.0f;
		XMUINT2 m_last_pressed_pos = { 0u,0u };

	public:
		camera_controller &operator=(const camera_controller&) = delete;
		camera_controller &operator=(camera_controller&&) = delete;
		camera_controller(const camera_controller&) = delete;
		camera_controller(camera_controller&&) = delete;
		camera_controller() = delete;
		camera_controller(pulsar::node *node, float movement_speed, float acceleration_speed, float lift_speed, float rotation_speed);
		~camera_controller() = default;

		void	execute(float delta_time);
	};
}
