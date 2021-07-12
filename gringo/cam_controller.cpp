
#include "cam_controller.h"
#include "grng_gfx.h"
#include "grng_input.h"
#include "grng_win_manager.h"


void		grng_cam_controller(void *data)
{
	GRNG_CAM_CONTROLLER *cam_controller = (GRNG_CAM_CONTROLLER*)data;

	GRNG_CAMERA *cam = GRNG_GFX::get_curr_camera();
	const XMFLOAT3 &cam_forward = cam->get_forward();
	const XMFLOAT3 &cam_right = cam->get_right();
	const XMFLOAT3 &cam_up = cam->get_up();
	GRNG_TRANSFORM &transform = cam->get_transform();

	float delta_time = GRNG_GFX::get_delta_time();
	bool is_rmb_pressed = GRNG_INPUT::GRNG_MOUSE::rmb_pressed();
	XMINT2 mouse_delta = GRNG_INPUT::GRNG_MOUSE::get_delta();

	if (is_rmb_pressed && !cam_controller->is_cursor_hidden)
	{
		cam_controller->last_pressed_pos = GRNG_INPUT::GRNG_MOUSE::get_global_pos();
		cam_controller->is_cursor_hidden = true;
		GRNG_WM::clamp_cursor_secure(GRNG_GFX::get_curr_win_id());
		GRNG_WM::hide_cursor_secure(GRNG_GFX::get_curr_win_id());
	}
	else if (!is_rmb_pressed && cam_controller->is_cursor_hidden)
	{
		GRNG_INPUT::GRNG_MOUSE::set_global_pos(cam_controller->last_pressed_pos.x, cam_controller->last_pressed_pos.y);
		cam_controller->is_cursor_hidden = false;
		GRNG_WM::free_cursor_secure(GRNG_GFX::get_curr_win_id());
		GRNG_WM::show_cursor_secure(GRNG_GFX::get_curr_win_id());
	}

	transform.position = transform.position + cam_forward * cam_controller->movement_speed * delta_time * is_rmb_pressed * ((GetKeyState('W') < 0) - (GetKeyState('S') < 0));
	transform.position = transform.position + cam_right * cam_controller->movement_speed * delta_time * is_rmb_pressed * ((GetKeyState('D') < 0) - (GetKeyState('A') < 0));
	transform.position = transform.position + cam_up * cam_controller->lift_speed * delta_time * is_rmb_pressed * ((GetKeyState('E') < 0) - (GetKeyState('Q') < 0));

	transform.rotation.y = grng_lerp(cam_controller->last_rot.y, transform.rotation.y + is_rmb_pressed * mouse_delta.x * cam_controller->rotation_speed * delta_time, cam_controller->rotation_sharpness);
	transform.rotation.x = grng_lerp(cam_controller->last_rot.x, transform.rotation.x + is_rmb_pressed * mouse_delta.y * cam_controller->rotation_speed * delta_time, cam_controller->rotation_sharpness);

	cam_controller->last_rot = { transform.rotation.x, transform.rotation.y };
}
