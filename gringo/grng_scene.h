#pragma once

#include "grng_piston.h"
#include "grng_def_scene.h"
#include "grng_scene_manager.h"
#include "grng_entity.h"
#include "grng_light.h"
#include "grng_skybox.h"
#include "grng_frag_const_buffer.h"


class grng_scene
{
private:
	int			id = -1;
	bool		is_alloc = false;

	GRNG_ENTITY_MANAGER										entity_manager;
	const GRNG_IPISTON<GRNG_ENTITY*, GRNG_MAX_ENTITY_COUNT>	*ientity = this->entity_manager.get_idata();

	GRNG_LIGHT_MANAGER										light_manager;
	const GRNG_IPISTON<GRNG_LIGHT*, GRNG_MAX_LIGHT_COUNT>	*ilight = this->light_manager.get_idata();

	GRNG_SHADER_LIGHT_SCENE								light_scene;
	GRNG_FRAG_CONST_BUFFER<GRNG_SHADER_LIGHT_SCENE>		light_scene_cbuffer;

	GRNG_SKYBOX		skybox;

public:
	grng_scene		&operator=(const grng_scene &s) = delete;
	grng_scene(const grng_scene &s) = delete;
	grng_scene(){ }

	int				get_id() const
	{
		return (this->id);
	}

	void			update_shader_light_scene()
	{
		this->light_scene.light_count = this->ilight->size;
		this->light_scene_cbuffer.set_slot(GRNG_DEFERRED_LIGHT_SLOT);
	
		int i = -1;
		while (++i < this->ilight->size)
		{
			GRNG_LIGHT *light_ptr = this->light_manager.get_data_secure(this->ilight->data[i].global_id);
			light_ptr->set_shader_light(this->light_scene.light[i]);
		}
	}

	void			add_entity(GRNG_ENTITY *entity);
	void			remove_entity(GRNG_ENTITY *entity);
	void			remove_entity(unsigned int id);
	GRNG_ENTITY		*get_entity(unsigned int id);

	void			add_light(GRNG_LIGHT *light);
	void			remove_light(GRNG_LIGHT *light);
	void			remove_light(unsigned int id);
	GRNG_LIGHT		*get_light(unsigned int id);

	void			set_skybox_material(const GRNG_SKYBOX_MATERIAL &mat);
	void			set_skybox_material(GRNG_SKYBOX_MATERIAL *mat);
	void			set_skybox_mesh(const GRNG_MESH &mesh);
	void			set_skybox_mesh(GRNG_MESH *mesh);

	static grng_scene	*create()
	{
		grng_scene *scene = new grng_scene;
		scene->id = GRNG_SM.add(scene);
		if (scene->id == -1)
		{
			delete scene;
			return (NULL);
		}
		scene->is_alloc = true;

		return (scene);
	}

	void			draw();
	void			draw_skybox();

	void			bind()
	{
		this->update_shader_light_scene();
		this->light_scene_cbuffer.update(this->light_scene);
		this->light_scene_cbuffer.bind();
	}
};

using GRNG_SCENE = grng_scene;
