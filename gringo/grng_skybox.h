#pragma once

#include "grng_gfx.h"
#include "grng_def.h"
#include "grng_input_layout.h"
#include "grng_vert_shader.h"
#include "grng_frag_shader.h"
#include "grng_sampler.h"
#include "grng_vert_const_buffer.h"
#include "grng_transform.h"
#include "grng_transform_shader.h"


class grng_skybox
{
private:
	GRNG_CUBEMAP		*env_map = (GRNG_CUBEMAP*)&GRNG_STD_CUBEMAP_BLACK;
	GRNG_MESH			*mesh = (GRNG_MESH*)&GRNG_STD_CUBE_MESH;

	static GRNG_VERT_SHADER		vs;
	static GRNG_FRAG_SHADER		fs;

	static GRNG_INPUT_LAYOUT	input_layout;
	static GRNG_SAMPLER			sampler;

	GRNG_SHADER_TRANSFORM									vert_transform;
	static GRNG_VERT_CONST_BUFFER<GRNG_SHADER_TRANSFORM>	transform_cbuffer;


	void		update_transform();

	void		copy_assign(const grng_skybox &s);

public:
	grng_skybox		&operator=(const grng_skybox &s);
	grng_skybox(const grng_skybox &s);
	grng_skybox();

	void		set_env_map(const GRNG_CUBEMAP &env_map);
	void		set_mesh(GRNG_MESH &mesh);

	void		draw()
	{
		if (!this->mesh)
			return;

		this->update_transform();

		grng_skybox::vs.bind();
		grng_skybox::fs.bind();
		this->env_map->bind();
		grng_skybox::sampler.bind();
		grng_skybox::input_layout.bind();

		GRNG_STD_FRONT_FACE_CULL_RS.bind();
		this->mesh->bind();
		this->mesh->draw();
	}
};

using GRNG_SKYBOX = grng_skybox;
