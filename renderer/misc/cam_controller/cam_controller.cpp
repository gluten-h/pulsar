//
//#include "cam_controller.h"
//
//
//void		cam_controller(void *data)
//{
//	CAM_CONTROLLER_DATA *cc_data = (CAM_CONTROLLER_DATA*)data;
//
//	PULSAR::CAMERA *cam = PULSAR::GFX::get_curr_camera();
//	const XMFLOAT3 &cam_forward = cam->get_forward();
//	const XMFLOAT3 &cam_right = cam->get_right();
//	const XMFLOAT3 &cam_up = cam->get_up();
//	PULSAR::TRANSFORM &transform = cam->get_transform();
//
//	float delta_time = PULSAR::GFX::get_delta_time();
//	bool is_rmb_pressed = PULSAR::MOUSE::rmb_pressed();
//	XMINT2 mouse_delta = PULSAR::MOUSE::get_delta();
//	PULSAR::WINDOW *win = PULSAR::GFX::get_curr_win();
//
//	if (is_rmb_pressed && !cc_data->is_cursor_hidden)
//	{
//		cc_data->last_pressed_pos = PULSAR::MOUSE::get_global_pos();
//		cc_data->is_cursor_hidden = true;
//		win->clamp_cursor();
//		win->hide_cursor();
//	}
//	else if (!is_rmb_pressed && cc_data->is_cursor_hidden)
//	{
//		PULSAR::MOUSE::set_global_pos(cc_data->last_pressed_pos.x, cc_data->last_pressed_pos.y);
//		cc_data->is_cursor_hidden = false;
//		win->free_cursor();
//		win->show_cursor();
//	}
//
//	transform.position = transform.position + cam_forward * cc_data->movement_speed * delta_time * is_rmb_pressed * ((GetKeyState('W') < 0) - (GetKeyState('S') < 0));
//	transform.position = transform.position + cam_right * cc_data->movement_speed * delta_time * is_rmb_pressed * ((GetKeyState('D') < 0) - (GetKeyState('A') < 0));
//	transform.position = transform.position + cam_up * cc_data->lift_speed * delta_time * is_rmb_pressed * ((GetKeyState('E') < 0) - (GetKeyState('Q') < 0));
//
//	transform.rotation.y = PULSAR::lerp(cc_data->last_rot.y, transform.rotation.y + is_rmb_pressed * mouse_delta.x * cc_data->rotation_speed * delta_time, cc_data->rotation_sharpness);
//	transform.rotation.x = PULSAR::lerp(cc_data->last_rot.x, transform.rotation.x + is_rmb_pressed * mouse_delta.y * cc_data->rotation_speed * delta_time, cc_data->rotation_sharpness);
//
//	cc_data->last_rot = { transform.rotation.x, transform.rotation.y };
//}
