
#include "grng_win_manager.h"


void			grng_wm::set_camera_secure(unsigned int win_id, GRNG_CAMERA &cam)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->set_camera(cam);
}
void			grng_wm::set_camera(unsigned int win_id, GRNG_CAMERA &cam)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
	win_ptr->set_camera(cam);
}

void			grng_wm::set_scene_secure(unsigned int win_id, GRNG_SCENE &scene)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->set_scene(scene);
}
void			grng_wm::set_scene(unsigned int win_id, GRNG_SCENE &scene)
{
	GRNG_WINDOW *win_ptr = grng_wm::win.get(win_id);
	win_ptr->set_scene(scene);
}
