
#include "win_manager.h"


void		PULSAR::WIN_MANAGER::set_camera_secure(unsigned int win_id, PULSAR::CAMERA *cam)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->set_camera(cam);
}
void		PULSAR::WIN_MANAGER::set_camera(unsigned int win_id, PULSAR::CAMERA *cam)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get(win_id);
	win_ptr->set_camera(cam);
}

void		PULSAR::WIN_MANAGER::set_scene_secure(unsigned int win_id, PULSAR::SCENE *scene)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get_secure(win_id);
	if (!win_ptr)
		return;
	win_ptr->set_scene(scene);
}
void		PULSAR::WIN_MANAGER::set_scene(unsigned int win_id, PULSAR::SCENE *scene)
{
	PULSAR::WINDOW *win_ptr = PULSAR::WIN_MANAGER::win.get(win_id);
	win_ptr->set_scene(scene);
}
