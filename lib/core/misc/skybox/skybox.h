#pragma once

#include "gfx.h"
#include "def_cubemaps.h"
#include "def_meshes.h"
#include "def_skybox_materials.h"
#include "def_rasterizer_states.h"
#include "def_skybox.h"
#include "input_layout.h"
#include "vert_shader.h"
#include "frag_shader.h"
#include "sampler.h"
#include "vert_const_buffer.h"
#include "transform.h"
#include "transform_shader.h"
#include "skybox_material.h"
#include "transform.h"


namespace PULSAR
{
	class SKYBOX
	{
	private:
		PULSAR::CUBEMAP				*env_map = (PULSAR::CUBEMAP*)&PULSAR::STD_CUBEMAP_BLACK;
		PULSAR::SKYBOX_MATERIAL		*material = (PULSAR::SKYBOX_MATERIAL*)&PULSAR::STD_SKYBOX_MATERIAL;
		PULSAR::MESH				*mesh = (PULSAR::MESH*)&PULSAR::STD_CUBE_MESH;

		static PULSAR::VERT_SHADER	vs;
		static PULSAR::FRAG_SHADER	fs;

		static PULSAR::INPUT_LAYOUT		input_layout;
		static PULSAR::SAMPLER			sampler;

		PULSAR::TRANSFORM	transform;


		void	copy_assign(const PULSAR::SKYBOX &s);

	public:
		SKYBOX		&operator=(const SKYBOX &s);
		SKYBOX(const SKYBOX &s);
		SKYBOX();

		void	set_material(const PULSAR::SKYBOX_MATERIAL &mat);
		void	set_material(PULSAR::SKYBOX_MATERIAL *mat);
		void	set_mesh(const PULSAR::MESH &mesh);
		void	set_mesh(PULSAR::MESH *mesh);

		void	draw()
		{
			if (!this->mesh || !this->material)
				return;

			this->transform.bind(PULSAR::BIND_SCOPE::LOCAL);
			this->material->bind(PULSAR::BIND_SCOPE::LOCAL);

			PULSAR::SKYBOX::vs.bind(PULSAR::BIND_SCOPE::LOCAL);
			PULSAR::SKYBOX::fs.bind(PULSAR::BIND_SCOPE::LOCAL);
			PULSAR::SKYBOX::sampler.bind(PULSAR::BIND_SCOPE::LOCAL);
			PULSAR::SKYBOX::input_layout.bind(PULSAR::BIND_SCOPE::LOCAL);

			STD_FRONT_FACE_CULL_RS.bind(PULSAR::BIND_SCOPE::LOCAL);
			this->mesh->bind(PULSAR::BIND_SCOPE::LOCAL);
			this->mesh->draw();

			PULSAR::BINDABLE::unbind_local();
		}
	};
}
