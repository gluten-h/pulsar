#pragma once

#include "grng_manager.h"
#include "grng_manager_ptr.h"
#include "grng_entities.h"
#include "grng_def.h"


class grng_entity_manager : public GRNG_MANAGER<GRNG_ENTITY, GRNG_MAX_ENTITY_COUNT>
{
private:
	void		add_event(int added_id, GRNG_ENTITY &data) override
	{
		data.id = added_id;
	}

	void		remove_event(int removed_id, GRNG_ENTITY &data) override
	{
		data.id = -1;
	}

public:
	grng_entity_manager() : GRNG_MANAGER<GRNG_ENTITY, GRNG_MAX_ENTITY_COUNT>(){ }

	GRNG_ENTITY		*add(const GRNG_ENTITY_TYPE &type)
	{
		if (!this->is_available())
			return (NULL);

		return (this->add_manager(GRNG_MANAGER_PTR::create_ptr(type)));
	}

	void		draw()
	{
		int i = -1;
		while (++i < this->idata->size)
		{
			(*this->idata->data[i].data)->draw();
		}
	}
};

using GRNG_ENTITY_MANAGER = grng_entity_manager;
