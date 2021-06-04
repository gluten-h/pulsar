
#include "win_proc.h"
#include "grng_camera.h"
#include "grng_math.h"
#include "grng_input.h"
#include "grng_gfx.h"


void		cam_look_proc(UINT msg, WPARAM w_param, void *data)
{
	GRNG_CAMERA *cam = GRNG_GFX::get_curr_camera();
	XMFLOAT3 &cam_pos = cam->get_position();
	XMFLOAT3 &cam_dir = cam->get_forward();
	GRNG_COMPONENT_TRANSFORM &transform = cam->get_transform();

	bool is_rmb_pressed = GRNG_INPUT::GRNG_MOUSE::is_rmb_pressed();
	XMINT2 mouse_delta = GRNG_INPUT::GRNG_MOUSE::get_delta();

	cam_pos = cam_pos + cam_dir * 1 * is_rmb_pressed * ((GetKeyState('W') < 0) - (GetKeyState('S') < 0));
	transform.rotation.y = transform.rotation.y + is_rmb_pressed * mouse_delta.x * 0.001f;
	transform.rotation.x = transform.rotation.x + is_rmb_pressed * mouse_delta.y * 0.001f;
}
