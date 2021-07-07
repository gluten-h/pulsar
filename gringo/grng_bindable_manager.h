#pragma once

#include "grng_manager.h"
#include "grng_manager_ptr.h"
#include "grng_scene_manager.h"
#include "grng_bindables.h"
#include "grng_def.h"


#define GRNG_BM GRNG_BINDABLE_MANAGER::get()


class grng_bindable_manager : public GRNG_MANAGER<GRNG_BINDABLE, GRNG_MAX_BINDABLE_COUNT>
{
private:
	void		add_event(int added_id, GRNG_BINDABLE &data) override
	{
		data.id = added_id;
	}

	void		remove_event(int removed_id, GRNG_BINDABLE &data) override
	{
		data.id = -1;

		for (auto &it : data.entity_scene_map)
		{
			GRNG_SCENE *scene = GRNG_SM.get_data_secure(it.second);
			if (scene)
			{
				GRNG_ENTITY *entity = scene->get_entity(it.first);
				if (entity)
					entity->erase_bindable(data);
			}
		}
	}

public:
	static grng_bindable_manager		&get()
	{
		static grng_bindable_manager manager;

		return (manager);
	}

	GRNG_BINDABLE		*add(const GRNG_BINDABLE_TYPE &type)
	{
		if (!this->is_available())
			return (NULL);

		return (this->add_manager(GRNG_MANAGER_PTR::create_ptr(type)));
	}
};

using GRNG_BINDABLE_MANAGER = grng_bindable_manager;
