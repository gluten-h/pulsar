#pragma once

#include "manager.h"
#include "def_misc.h"


namespace PULSAR
{
	class COMPONENT;

	class COMPONENT_MANAGER : public PULSAR::MANAGER<COMPONENT, PULSAR::MAX_COMPONENT_COUNT>
	{
	public:
		static COMPONENT_MANAGER	&get_instance()
		{
			static COMPONENT_MANAGER manager;

			return (manager);
		}

		int		add(COMPONENT *component)
		{
			if (!this->is_available(component))
				return (-1);
			return (this->add_manager(component));
		}
	};
}
