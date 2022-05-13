
#include "scene.h"


//void		PULSAR::scene::add_light(PULSAR::LIGHT *light)
//{
//	int id = this->light_manager.add(light);
//	if (id > -1)
//		light->add_to_scene(this->id, id);
//}
//
//void		PULSAR::scene::remove_light(PULSAR::LIGHT *light)
//{
//	if (light->get_local_id(this->id) == -1)
//		return;
//
//	this->light_manager.remove(light);
//	light->remove_from_scene(this->id);
//}
//
//void		PULSAR::scene::remove_light(unsigned int light_id)
//{
//	PULSAR::LIGHT *light_ptr = this->light_manager.get_elem(light_id);
//	if (!light_ptr)
//		return;
//
//	if (light_ptr->get_local_id(this->id) == -1)
//		return;
//
//	this->light_manager.remove(light_ptr);
//	light_ptr->remove_from_scene(this->id);
//}
//
//PULSAR::LIGHT		*PULSAR::scene::get_light(unsigned int light_id)
//{
//	return (this->light_manager.get_elem(light_id));
//}
