#pragma once

#include "manager.h"
#include "def_scene.h"


namespace PULSAR
{
#define LM LIGHT_MANAGER::get()
	//const LIGHT_MANAGER &LM = LIGHT_MANAGER::get();


	class LIGHT;


	class LIGHT_MANAGER : public PULSAR::MANAGER<LIGHT, PULSAR::MAX_LIGHT_COUNT>
	{
	public:
		static LIGHT_MANAGER	&get()
		{
			static LIGHT_MANAGER manager;

			return (manager);
		}

		int		add(LIGHT *light)
		{
			if (!this->is_available(light))
				return (-1);
			return (this->add_manager(light));
		}
	};
}
