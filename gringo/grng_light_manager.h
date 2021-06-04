#pragma once

#include "grng_manager.h"
#include "grng_bindables.h"
#include "grng_lights.h"
#include "grng_scene_def.h"
#include "grng_deffered_def.h"


class grng_light_manager : public GRNG_MANAGER<GRNG_LIGHT, GRNG_MAX_LIGHT_COUNT>
{
private:
	static GRNG_FRAG_CONST_BUFFER<GRNG_SHADER_LIGHT_SCENE>		light_scene_cbuffer;
	GRNG_SHADER_LIGHT_SCENE										light_scene;


	void		update_shader_light_scene()
	{
		this->light_scene.light_count = this->idata->size;

		int i = -1;
		while (++i < this->idata->size)
		{
			GRNG_LIGHT *light_ptr = *this->data.get(this->idata->data[i].global_id);
			light_ptr->set_shader_light(this->light_scene.light[i]);
		}
	}


	void		add_event(int added_id) override
	{
		this->update_shader_light_scene();
	}

	void		remove_event(int removed_id) override
	{
		this->update_shader_light_scene();
	}

public:
	grng_light_manager() : GRNG_MANAGER<GRNG_LIGHT, GRNG_MAX_LIGHT_COUNT>()
	{
		grng_light_manager::light_scene_cbuffer.set_slot(GRNG_DEFERRED_LIGHT_SLOT);
	}


	void		bind() override
	{
		this->light_scene_cbuffer.update(this->light_scene);
		this->light_scene_cbuffer.bind();
	}
};

using GRNG_LIGHT_MANAGER = grng_light_manager;
