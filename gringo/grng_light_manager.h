#pragma once

#include "grng_manager.h"
#include "grng_def_scene.h"


#define GRNG_LM GRNG_LIGHT_MANAGER::get()


class grng_light;


class grng_light_manager : public GRNG_MANAGER<grng_light, GRNG_MAX_LIGHT_COUNT>
{
public:
	static grng_light_manager		&get()
	{
		static grng_light_manager manager;

		return (manager);
	}

	int		add(grng_light *light)
	{
		if (!this->is_available(light))
			return (-1);
		return (this->add_manager(light));
	}
};

using GRNG_LIGHT_MANAGER = grng_light_manager;
