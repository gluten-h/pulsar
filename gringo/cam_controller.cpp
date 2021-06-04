
#include "cam_controller.h"
#include "grng_gfx.h"
#include "grng_input.h"


void		grng_cam_controller(void *data)
{
	GRNG_CAM_CONTROLLER *cam_controller = (GRNG_CAM_CONTROLLER*)data;

	GRNG_CAMERA *cam = GRNG_GFX::get_curr_camera();
	const XMFLOAT3 &cam_forward = cam->get_forward();
	const XMFLOAT3 &cam_right = cam->get_right();
	const XMFLOAT3 &cam_up = cam->get_up();
	GRNG_COMPONENT_TRANSFORM &transform = cam->get_transform();

	float fps = GRNG_GFX::get_fps();
	bool is_rmb_pressed = GRNG_INPUT::GRNG_MOUSE::is_rmb_pressed();
	XMINT2 mouse_delta = GRNG_INPUT::GRNG_MOUSE::get_delta();

	transform.position = transform.position + cam_forward * cam_controller->movement_speed * fps * is_rmb_pressed * ((GetKeyState('W') < 0) - (GetKeyState('S') < 0));
	transform.position = transform.position + cam_right * cam_controller->movement_speed * fps * is_rmb_pressed * ((GetKeyState('D') < 0) - (GetKeyState('A') < 0));
	transform.position = transform.position + cam_up * cam_controller->lift_speed * fps * is_rmb_pressed * ((GetKeyState('E') < 0) - (GetKeyState('Q') < 0));

	transform.rotation.y = transform.rotation.y + is_rmb_pressed * mouse_delta.x * cam_controller->rotation_speed;
	transform.rotation.x = transform.rotation.x + is_rmb_pressed * mouse_delta.y * cam_controller->rotation_speed;
}
