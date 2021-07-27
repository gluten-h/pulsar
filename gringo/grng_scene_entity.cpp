
#include "grng_scene.h"


GRNG_ENTITY			*grng_scene::add_entity(const GRNG_ENTITY_TYPE &type)
{
	GRNG_ENTITY *entity = this->entity_manager.add(type);
	entity->scene_id = this->id;

	return (entity);
}

void				grng_scene::remove_entity(GRNG_ENTITY &drawable)
{
	this->entity_manager.remove_secure(drawable);
}

void				grng_scene::remove_entity(unsigned int id)
{
	this->entity_manager.remove_secure(id);
}

GRNG_ENTITY			*grng_scene::get_entity(unsigned int id)
{
	return (this->entity_manager.get_data_secure(id));
}
