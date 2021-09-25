#pragma once

#include "manager.h"
#include "def_scene.h"


namespace PULSAR
{
	class LIGHT;

	class LIGHT_MANAGER : public PULSAR::MANAGER<LIGHT, PULSAR::MAX_LIGHT_COUNT>
	{
	public:
		static LIGHT_MANAGER	&get_instance()
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
