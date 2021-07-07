#pragma once

#include "grng_manager.h"
#include "grng_scene.h"
#include "grng_def.h"


#define GRNG_SM GRNG_SCENE_MANAGER::get()


class grng_scene_manager : public GRNG_MANAGER<GRNG_SCENE, GRNG_MAX_SCENE_COUNT>
{
private:
	void				add_event(int added_id, GRNG_SCENE &data)
	{
		data.id = added_id;
	}

	void				remove_event(int removed_id, GRNG_SCENE &data)
	{
		data.id = -1;
	}

public:
	static grng_scene_manager		&get()
	{
		static grng_scene_manager manager;

		return (manager);
	}

	GRNG_SCENE		*add()
	{
		if (!this->is_available())
			return (NULL);

		GRNG_SCENE *new_scene = new GRNG_SCENE;

		return (this->add_manager(new_scene));
	}
};

using GRNG_SCENE_MANAGER = grng_scene_manager;
