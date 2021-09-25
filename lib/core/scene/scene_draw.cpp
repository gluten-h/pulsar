
#include "scene.h"


void		PULSAR::SCENE::draw()
{
	for (auto &it : this->entity_manager)
	{
		it.data->draw();
	}
}

void		PULSAR::SCENE::draw_skybox()
{
	this->skybox.draw();
}
