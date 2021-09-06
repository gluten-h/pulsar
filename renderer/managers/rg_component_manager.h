#pragma once

#include "manager.h"
#include "def_misc.h"


namespace PULSAR
{
#define RGCM RG_COMPONENT_MANAGER::get()
	//const RG_COMPONENT_MANAGER &RGCM = RG_COMPONENT_MANAGER::get();


	class RG_COMPONENT;


	class RG_COMPONENT_MANAGER : public PULSAR::MANAGER<RG_COMPONENT, PULSAR::MAX_RG_COMPONENT_COUNT>
	{
	public:
		static RG_COMPONENT_MANAGER		&get()
		{
			static RG_COMPONENT_MANAGER manager;

			return (manager);
		}

		int		add(RG_COMPONENT *rg_component)
		{
			if (!this->is_available(rg_component))
				return (-1);
			return (this->add_manager(rg_component));
		}
	};
}
