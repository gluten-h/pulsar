
#include "grng_scene.h"


GRNG_LIGHT			*grng_scene::add_light(const GRNG_LIGHT_TYPE &type)
{
	return (this->light_manager.add(type));
}

void				grng_scene::remove_light(GRNG_LIGHT &light)
{
	this->light_manager.remove_secure(light);
}

void				grng_scene::remove_light(unsigned int id)
{
	this->light_manager.remove_secure(id);
}

GRNG_LIGHT			*grng_scene::get_light(unsigned int id)
{
	return (this->light_manager.get_data_secure(id));
}
