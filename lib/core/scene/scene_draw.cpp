
#include "scene.h"


void		PULSAR::scene::draw()
{
	for (auto &it : this->entity_manager)
	{
		it.data->draw();
	}
}

void		PULSAR::scene::draw_skybox()
{
	this->skybox.draw();
}
