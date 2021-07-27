#pragma once

#include "grng_gfx.h"
#include "grng_def_cubemaps.h"
#include "grng_def_meshes.h"
#include "grng_def_skybox_materials.h"
#include "grng_def_rasterizer_states.h"
#include "grng_def_skybox.h"
#include "grng_input_layout.h"
#include "grng_vert_shader.h"
#include "grng_frag_shader.h"
#include "grng_sampler.h"
#include "grng_vert_const_buffer.h"
#include "grng_transform.h"
#include "grng_transform_shader.h"
#include "grng_skybox_material.h"
#include "grng_transform.h"


class grng_skybox
{
private:
	GRNG_CUBEMAP			*env_map = (GRNG_CUBEMAP*)&GRNG_STD_CUBEMAP_BLACK;
	GRNG_SKYBOX_MATERIAL	*material = (GRNG_SKYBOX_MATERIAL*)&GRNG_STD_SKYBOX_MATERIAL;
	GRNG_MESH				*mesh = (GRNG_MESH*)&GRNG_STD_CUBE_MESH;

	static GRNG_VERT_SHADER		vs;
	static GRNG_FRAG_SHADER		fs;

	static GRNG_INPUT_LAYOUT	input_layout;
	static GRNG_SAMPLER			sampler;

	GRNG_TRANSFORM				transform;


	void		copy_assign(const grng_skybox &s);

public:
	grng_skybox		&operator=(const grng_skybox &s);
	grng_skybox(const grng_skybox &s);
	grng_skybox();

	void		set_material(const GRNG_SKYBOX_MATERIAL &mat);
	void		set_mesh(const GRNG_MESH &mesh);

	void		draw()
	{
		if (!this->mesh || !this->material)
			return;

		this->transform.bind();
		this->material->bind();

		grng_skybox::vs.bind();
		grng_skybox::fs.bind();
		grng_skybox::sampler.bind();
		grng_skybox::input_layout.bind();

		GRNG_STD_FRONT_FACE_CULL_RS.bind();
		this->mesh->bind();
		this->mesh->draw();
	}
};

using GRNG_SKYBOX = grng_skybox;
