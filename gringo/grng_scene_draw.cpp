
#include "grng_scene.h"


void				grng_scene::draw()
{
	//this->entity_manager.draw();

	int i = -1;
	while (++i < this->ientity->size)
	{
		(*this->ientity->data[i].data)->draw();
	}
}

void				grng_scene::draw_skybox()
{
	this->skybox.draw();
}
