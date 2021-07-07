
#include "grng_window.h"


void		grng_window::set_camera(GRNG_CAMERA &cam)
{
	this->curr_camera = &cam;
}

void		grng_window::set_scene(GRNG_SCENE &scene)
{
	this->curr_scene = &scene;
}
