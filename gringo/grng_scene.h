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
	grng_scene		&operator=(const grng_scene &s) = delete;
	grng_scene(const grng_scene &s) = delete;
	grng_scene(){ }

	int					get_id() const
	{
		return (this->id);
	}

	GRNG_LIGHT			*add_light(const GRNG_LIGHT_TYPE &type);
	void				remove_light(GRNG_LIGHT &light);
	void				remove_light(unsigned int id);
	GRNG_LIGHT			*get_light(unsigned int id);

	GRNG_ENTITY			*add_entity(const GRNG_ENTITY_TYPE &type);
	void				remove_entity(GRNG_ENTITY &drawable);
	void				remove_entity(unsigned int id);
	GRNG_ENTITY			*get_entity(unsigned int id);

	void				set_skybox_material(const GRNG_SKYBOX_MATERIAL &mat);
	void				set_skybox_mesh(const GRNG_MESH &mesh);

	void				draw();
	void				draw_skybox();

	void				bind()
	{
		this->light_manager.bind();
	}
};

using GRNG_SCENE = grng_scene;
