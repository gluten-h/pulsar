#pragma once

#include "grng_entity.h"
#include "grng_bindable.h"

#include <unordered_set>


class grng_bindable_entity : public GRNG_ENTITY
{
protected:
	std::unordered_set<GRNG_BINDABLE*>		bindables;

public:
	grng_bindable_entity() : GRNG_ENTITY(){ }
	~grng_bindable_entity()
	{
		for (auto &it : this->bindables)
			it->remove_from_entity(this);
		this->bindables.clear();
	}

	void		add_bindable(GRNG_BINDABLE *bindable)
	{
		this->bindables.insert(bindable);
		bindable->add_to_entity(this);
	}
	void		remove_bindable(GRNG_BINDABLE *bindable)
	{
		this->bindables.erase(bindable);
		bindable->remove_from_entity(this);
	}
	void		_remove_bindable_ignore_entity(GRNG_BINDABLE *bindable)
	{
		this->bindables.erase(bindable);
	}

	void		bind()
	{
		for (auto &b : this->bindables)
			b->bind(GRNG_BIND_SCOPE::LOCAL);
	}
};

using GRNG_BINDABLE_ENTITY = grng_bindable_entity;
