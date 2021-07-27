
#include "grng_scene.h"


void				grng_scene::draw()
{
	this->entity_manager.draw();
}

void				grng_scene::draw_skybox()
{
	this->skybox.draw();
}
