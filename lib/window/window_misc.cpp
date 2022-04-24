
#include "window.h"


void		PULSAR::WINDOW::set_camera(PULSAR::CAMERA *cam)
{
	this->curr_camera = cam;
}

void		PULSAR::WINDOW::set_scene(scene *scene)
{
	this->curr_scene = scene;
}


HWND		PULSAR::WINDOW::get_hwnd() const
{
	return (this->hwnd);
}
