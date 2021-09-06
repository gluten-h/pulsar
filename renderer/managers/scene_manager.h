#pragma once

#include "manager.h"
#include "def_misc.h"


namespace PULSAR
{
#define SM SCENE_MANAGER::get()
	//const SCENE_MANAGER &SM = SCENE_MANAGER::get();


	class SCENE;


	class SCENE_MANAGER : public PULSAR::MANAGER<SCENE, PULSAR::MAX_SCENE_COUNT>
	{
	public:
		static SCENE_MANAGER	&get()
		{
			static SCENE_MANAGER manager;

			return (manager);
		}

		int		add(SCENE *scene)
		{
			if (!this->is_available(scene))
				return (-1);
			return (this->add_manager(scene));
		}
	};
}
