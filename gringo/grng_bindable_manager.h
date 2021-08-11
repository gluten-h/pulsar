#pragma once

#include "grng_manager.h"
#include "grng_def_misc.h"


#define GRNG_BM GRNG_BINDABLE_MANAGER::get()


class grng_bindable;


class grng_bindable_manager : public GRNG_MANAGER<grng_bindable, GRNG_MAX_BINDABLE_COUNT>
{
public:
	static grng_bindable_manager		&get()
	{
		static grng_bindable_manager manager;

		return (manager);
	}

	int		add(grng_bindable *bindable)
	{
		if (!this->is_available(bindable))
			return (-1);
		return (this->add_manager(bindable));
	}
};

using GRNG_BINDABLE_MANAGER = grng_bindable_manager;
