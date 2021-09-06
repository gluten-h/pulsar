#pragma once

#include "entity.h"
#include "bindable.h"

#include <unordered_set>


namespace PULSAR
{
	class BINDABLE_ENTITY : public PULSAR::ENTITY
	{
	protected:
		std::unordered_set<BINDABLE*>	bindables;

	public:
		BINDABLE_ENTITY() : PULSAR::ENTITY(){ }
		~BINDABLE_ENTITY()
		{
			for (auto &it : this->bindables)
				it->remove_from_entity(this);
			this->bindables.clear();
		}

		void		add_bindable(PULSAR::BINDABLE *bindable)
		{
			this->bindables.insert(bindable);
			bindable->add_to_entity(this);
		}
		void		remove_bindable(PULSAR::BINDABLE *bindable)
		{
			this->bindables.erase(bindable);
			bindable->remove_from_entity(this);
		}
		void		_remove_bindable_ignore_entity(PULSAR::BINDABLE *bindable)
		{
			this->bindables.erase(bindable);
		}

		void		bind()
		{
			for (auto &b : this->bindables)
				b->bind(PULSAR::BIND_SCOPE::LOCAL);
		}
	};
}
