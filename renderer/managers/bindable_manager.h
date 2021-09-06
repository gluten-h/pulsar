#pragma once

#include "manager.h"
#include "def_misc.h"


namespace PULSAR
{
#define BM BINDABLE_MANAGER::get()
	//const BINDABLE_MANAGER &BM = BINDABLE_MANAGER::get();


	class BINDABLE;


	class BINDABLE_MANAGER : public PULSAR::MANAGER<BINDABLE, PULSAR::MAX_BINDABLE_COUNT>
	{
	public:
		static BINDABLE_MANAGER		&get()
		{
			static BINDABLE_MANAGER manager;

			return (manager);
		}

		int		add(BINDABLE *bindable)
		{
			if (!this->is_available(bindable))
				return (-1);
			return (this->add_manager(bindable));
		}
	};
}
