#pragma once

#include "grng_manager.h"
#include "grng_manager_ptr.h"
#include "grng_component.h"
#include "grng_def.h"


#define GRNG_CM GRNG_COMPONENT_MANAGER::get()


class grng_component_manager : public GRNG_MANAGER<GRNG_COMPONENT, GRNG_MAX_BINDABLE_COUNT>
{
private:
	void		add_event(int added_id, GRNG_COMPONENT &data) override
	{
		data.id = added_id;
	}

	void		remove_event(int removed_id, GRNG_COMPONENT &data) override
	{
		data.id = -1;
	}

public:
	static grng_component_manager		&get()
	{
		static grng_component_manager manager;

		return (manager);
	}

	GRNG_COMPONENT		*add(GRNG_COMPONENT_TYPE type)
	{
		if (!this->is_available())
			return (NULL);

		return (this->add_manager(GRNG_MANAGER_PTR::create_ptr(type)));
	}
};

using GRNG_COMPONENT_MANAGER = grng_component_manager;
