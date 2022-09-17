
#include "camera_controller.h"
#include "utils/math.h"
#include "node/node.h"
#include "window/window.h"
#include "input/pulsar_input.h"
#include "transform/transform_component.h"


pulsar::camera_controller::camera_controller(pulsar::node *node, float movement_speed, float acceleration_speed, float lift_speed, float rotation_speed)
{
	this->mp_node = node;
	this->m_movement_speed = movement_speed;
	this->m_acc_speed = acceleration_speed;
	this->m_lift_speed = lift_speed;
	this->m_rotation_speed = rotation_speed;
}

void	pulsar::camera_controller::execute(float delta_time)
{
	pulsar::window *win = pulsar::window::active_window();
	bool is_rmb_pressed = pulsar::input::is_buton_pressed(pulsar::RMB);
	XMINT2 mouse_delta = pulsar::input::mouse_delta();

	if (is_rmb_pressed && !win->is_cursor_hidden())
	{
		this->m_last_pressed_pos = pulsar::input::get_mouse_position();
		win->clamp_cursor();
		win->hide_cursor();
	}
	else if (!is_rmb_pressed && win->is_cursor_hidden())
	{
		pulsar::input::set_mouse_position(this->m_last_pressed_pos.x, this->m_last_pressed_pos.y);
		win->free_cursor();
		win->show_cursor();
	}

	pulsar::transform &transform = this->mp_node->get_component<pulsar::transform_component>().transform;
	XMFLOAT4 rot_f4 = transform.get_rotation();
	XMVECTOR rot = XMLoadFloat4(&rot_f4);
	XMFLOAT3 right = transform.right();
	XMFLOAT3 pos = transform.get_position();

	float is_rot = is_rmb_pressed * this->m_rotation_speed * delta_time;
	float is_mov = is_rmb_pressed * pulsar::lerp(this->m_movement_speed, this->m_acc_speed, (float)pulsar::input::is_key_pressed(pulsar::KEY_LSHIFT)) * delta_time;

	rot = XMQuaternionMultiply(rot, XMQuaternionRotationNormal(XMLoadFloat3(&right), is_rot * mouse_delta.y));
	rot = XMQuaternionMultiply(rot, XMQuaternionRotationNormal(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), is_rot * mouse_delta.x));

	pos = pos + transform.forward() * is_mov * (pulsar::input::is_key_pressed(pulsar::KEY_W) - pulsar::input::is_key_pressed(pulsar::KEY_S));
	pos = pos + transform.right() * is_mov * (pulsar::input::is_key_pressed(pulsar::KEY_D) - pulsar::input::is_key_pressed(pulsar::KEY_A));
	pos = pos + transform.up() * is_mov * (pulsar::input::is_key_pressed(pulsar::KEY_E) - pulsar::input::is_key_pressed(pulsar::KEY_Q));

	XMStoreFloat4(&rot_f4, rot);
	transform.set_rotation(rot_f4);
	transform.set_position(pos);
}
