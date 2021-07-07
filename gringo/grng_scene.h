#pragma once

#include "grng_light_manager.h"
#include "grng_entity_manager.h"
#include "grng_cubemap.h"
#include "grng_mesh.h"
#include "grng_def.h"


class grng_scene
{
private:
	friend class grng_scene_manager;

private:
	int						id = -1;

	GRNG_LIGHT_MANAGER		light_manager;
	GRNG_ENTITY_MANAGER		entity_manager;

	GRNG_CUBEMAP			*env_map = NULL;
	static GRNG_MESH		skybox_mesh;

public:
	int					get_id() const
	{
		return (this->id);
	}


	GRNG_LIGHT			*add_light(const GRNG_LIGHT_TYPE &type)
	{
		return (this->light_manager.add(type));
	}

	void			remove_light(GRNG_LIGHT &light)
	{
		this->light_manager.remove_secure(light);
	}

	void			remove_light(unsigned int id)
	{
		this->light_manager.remove_secure(id);
	}

	GRNG_LIGHT		*get_light(unsigned int id)
	{
		return (this->light_manager.get_data_secure(id));
	}


	GRNG_ENTITY			*add_entity(const GRNG_ENTITY_TYPE &type)
	{
		GRNG_ENTITY *entity = this->entity_manager.add(type);
		entity->scene_id = this->id;

		return (entity);
	}

	void			remove_entity(GRNG_ENTITY &drawable)
	{
		this->entity_manager.remove_secure(drawable);
	}

	void			remove_entity(unsigned int id)
	{
		this->entity_manager.remove_secure(id);
	}

	GRNG_ENTITY		*get_entity(unsigned int id)
	{
		return (this->entity_manager.get_data_secure(id));
	}


	void			set_env_map(GRNG_CUBEMAP &env_map)
	{
		this->env_map = &env_map;
	}

	GRNG_CUBEMAP	*get_env_map()
	{
		return (this->env_map);
	}


	void			draw()
	{
		this->entity_manager.draw();
	}

	void			bind()
	{
		this->light_manager.bind();
	}
};

using GRNG_SCENE = grng_scene;
