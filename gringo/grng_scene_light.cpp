
#include "grng_scene.h"


void			grng_scene::add_light(GRNG_LIGHT *light)
{
	int id = this->light_manager.add(light);
	if (id > -1)
		light->add_to_scene(this->id, id);
}

void			grng_scene::remove_light(GRNG_LIGHT *light)
{
	if (light->get_local_id(this->id) == -1)
		return;

	this->light_manager.remove_secure(light);
	light->remove_from_scene(this->id);
}

void			grng_scene::remove_light(unsigned int light_id)
{
	GRNG_LIGHT *light_ptr = this->light_manager.get_data_secure(light_id);
	if (!light_ptr)
		return;

	if (light_ptr->get_local_id(this->id) == -1)
		return;

	this->light_manager.remove_secure(light_ptr);
	light_ptr->remove_from_scene(this->id);
}

GRNG_LIGHT		*grng_scene::get_light(unsigned int light_id)
{
	return (this->light_manager.get_data_secure(light_id));
}
