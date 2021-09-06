#pragma once

#include "manager.h"
#include "def_scene.h"


namespace PULSAR
{
#define EM ENTITY_MANAGER::get()
	//const ENTITY_MANAGER &EM = ENTITY_MANAGER::get();


	class ENTITY;


	class ENTITY_MANAGER : public PULSAR::MANAGER<ENTITY, PULSAR::MAX_ENTITY_COUNT>
	{
	public:
		static ENTITY_MANAGER	&get()
		{
			static ENTITY_MANAGER manager;

			return (manager);
		}

		int		add(ENTITY *entity)
		{
			if (!this->is_available(entity))
				return (-1);
			return (this->add_manager(entity));
		}
	};
}
