#pragma once

#include "grng_manager.h"
#include "grng_def.h"


#define GRNG_SM GRNG_SCENE_MANAGER::get()


class grng_scene;


class grng_scene_manager : public GRNG_MANAGER<grng_scene, GRNG_MAX_SCENE_COUNT>
{
public:
	static grng_scene_manager		&get()
	{
		static grng_scene_manager manager;

		return (manager);
	}

	int		add(grng_scene *scene)
	{
		if (!this->is_available(scene))
			return (-1);
		return (this->add_manager(scene));
	}
};

using GRNG_SCENE_MANAGER = grng_scene_manager;
