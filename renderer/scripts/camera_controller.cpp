
#include "camera_controller.h"
#include "window/window.h"
#include "input/pulsar_input.h"
#include "transform/transform_component.h"


pulsar::camera_controller::camera_controller(pulsar::node *node, float movement_speed, float lift_speed, float rotation_speed) : pulsar::script(node)
{
	this->m_movement_speed = movement_speed;
	this->m_lift_speed = lift_speed;
	this->m_rotation_speed = rotation_speed;
}

void	pulsar::camera_controller::execute(float delta_time)
{
	//	CAM_CONTROLLER_DATA *cc_data = (CAM_CONTROLLER_DATA*)data;

	//	pulsar::CAMERA *cam = pulsar::gfx::instance_curr_camera();
	//	const XMFLOAT3 &cam_forward = cam->get_forward();
	//	const XMFLOAT3 &cam_right = cam->get_right();
	//	const XMFLOAT3 &cam_up = cam->get_up();
	//	pulsar::TRANSFORM &transform = cam->get_transform();

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
	XMFLOAT3 rot = transform.get_rotation();
	XMFLOAT3 pos = transform.get_position();

	//	transform.position = transform.position + cam_forward * cc_data->movement_speed * delta_time * is_rmb_pressed * ((GetKeyState('W') < 0) - (GetKeyState('S') < 0));
	//	transform.position = transform.position + cam_right * cc_data->movement_speed * delta_time * is_rmb_pressed * ((GetKeyState('D') < 0) - (GetKeyState('A') < 0));
	//	transform.position = transform.position + cam_up * cc_data->lift_speed * delta_time * is_rmb_pressed * ((GetKeyState('E') < 0) - (GetKeyState('Q') < 0));

	float is_rot = is_rmb_pressed * this->m_rotation_speed * delta_time;	
	float is_mov = is_rmb_pressed * this->m_movement_speed * delta_time;

	rot.x += is_rot * mouse_delta.y;
	rot.y += is_rot * mouse_delta.x;



	transform.set_rotation(rot);
	transform.set_position(pos);


	//	transform.rotation.y = pulsar::lerp(cc_data->last_rot.y, transform.rotation.y + is_rmb_pressed * mouse_delta.x * cc_data->rotation_speed * delta_time, cc_data->rotation_sharpness);
	//	transform.rotation.x = pulsar::lerp(cc_data->last_rot.x, transform.rotation.x + is_rmb_pressed * mouse_delta.y * cc_data->rotation_speed * delta_time, cc_data->rotation_sharpness);

	//	cc_data->last_rot = { transform.rotation.x, transform.rotation.y };
}
