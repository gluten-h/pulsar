
#include "grng_scene.h"


void			grng_scene::add_entity(GRNG_ENTITY *entity)
{
	 int id = this->entity_manager.add(entity);
	if (id > -1)
		entity->add_to_scene(this->id, id);
}

void			grng_scene::remove_entity(GRNG_ENTITY *entity)
{
	if (entity->get_local_id(this->id) == -1)
		return;

	this->entity_manager.remove_secure(entity);
	entity->remove_from_scene(this->id);
}

void			grng_scene::remove_entity(unsigned int entity_id)
{
	GRNG_ENTITY *entity_ptr = this->entity_manager.get_data_secure(entity_id);
	if (!entity_ptr)
		return;

	if (entity_ptr->get_local_id(this->id) == -1)
		return;

	this->entity_manager.remove_secure(entity_ptr);
	entity_ptr->remove_from_scene(this->id);
}

GRNG_ENTITY		*grng_scene::get_entity(unsigned int entity_id)
{
	return (this->entity_manager.get_data_secure(entity_id));
}
