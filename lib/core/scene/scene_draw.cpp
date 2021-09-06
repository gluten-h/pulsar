
#include "scene.h"


void		PULSAR::SCENE::draw()
{
	//this->entity_manager.draw();

	int i = -1;
	while (++i < this->ientity->size)
	{
		(*this->ientity->data[i].data)->draw();
	}
}

void		PULSAR::SCENE::draw_skybox()
{
	this->skybox.draw();
}
