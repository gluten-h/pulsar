#pragma once

#include "grng_manager.h"
#include "grng_def_misc.h"


#define GRNG_CM GRNG_COMPONENT_MANAGER::get()


class grng_component;


class grng_component_manager : public GRNG_MANAGER<grng_component, GRNG_MAX_BINDABLE_COUNT>
{
public:
	static grng_component_manager		&get()
	{
		static grng_component_manager manager;

		return (manager);
	}

	int		add(grng_component *component)
	{
		if (!this->is_available(component))
			return (-1);
		return (this->add_manager(component));
	}
};

using GRNG_COMPONENT_MANAGER = grng_component_manager;
