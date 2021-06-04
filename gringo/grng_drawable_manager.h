#pragma once

#include "grng_manager.h"
#include "grng_drawable.h"
#include "grng_scene_def.h"


class grng_drawable_manager : public GRNG_MANAGER<GRNG_DRAWABLE, GRNG_MAX_DRAWABLE_COUNT>
{
private:
	void		add_event(int added_id) override{ }
	void		remove_event(int removed_id) override{ }

public:
	grng_drawable_manager() : GRNG_MANAGER<GRNG_DRAWABLE, GRNG_MAX_DRAWABLE_COUNT>(){ }

	void		bind() override{ }

	void		draw()
	{
		int i = -1;
		while (++i < this->idata->size)
		{
			(*this->idata->data[i].data)->draw();
		}
	}
};

using GRNG_DRAWABLE_MANAGER = grng_drawable_manager;
