#pragma once

#include "grng_light_manager.h"
#include "grng_entity_manager.h"
#include "grng_skybox.h"


class grng_scene
{
	friend class grng_scene_manager;

private:
	int						id = -1;

	GRNG_LIGHT_MANAGER		light_manager;
	GRNG_ENTITY_MANAGER		entity_manager;

	GRNG_SKYBOX				skybox;

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
		this->skybox.set_env_map(env_map);
	}

	void			set_skybox_mesh(GRNG_MESH &mesh)
	{
		this->skybox.set_mesh(mesh);
	}


	void			draw()
	{
		this->entity_manager.draw();
	}

	void			draw_skybox()
	{
		this->skybox.draw();
	}

	void			bind()
	{
		this->light_manager.bind();
	}
};

using GRNG_SCENE = grng_scene;
