#pragma once

#include "grng_manager.h"
#include "grng_def_scene.h"


#define GRNG_EM GRNG_ENTITY_MANAGER::get()


class grng_entity;


class grng_entity_manager : public GRNG_MANAGER<grng_entity, GRNG_MAX_ENTITY_COUNT>
{
public:
	static grng_entity_manager		&get()
	{
		static grng_entity_manager manager;

		return (manager);
	}

	int		add(grng_entity *entity)
	{
		if (!this->is_available(entity))
			return (-1);
		return (this->add_manager(entity));
	}
};

using GRNG_ENTITY_MANAGER = grng_entity_manager;
