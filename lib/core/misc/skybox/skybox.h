//#pragma once
//
//#include "gfx.h"
//#include "def/cubemaps.h"
//#include "def/meshes.h"
//#include "def/skybox_materials.h"
//#include "def/rasterizer_states.h"
//#include "def/skybox.h"
//#include "input_layout/input_layout.h"
//#include "shaders/vert_shader.h"
//#include "shaders/frag_shader.h"
//#include "sampler/sampler.h"
//#include "const_buffers/vert_const_buffer.h"
//#include "transform.h"
//#include "transform_shader.h"
//#include "skybox_material.h"
//#include "transform.h"
//
//
//namespace PULSAR
//{
//	class SKYBOX
//	{
//	private:
//		PULSAR::CUBEMAP				*env_map = (PULSAR::CUBEMAP*)&PULSAR::STD_CUBEMAP_BLACK;
//		PULSAR::SKYBOX_MATERIAL		*material = (PULSAR::SKYBOX_MATERIAL*)&PULSAR::STD_SKYBOX_MATERIAL;
//		PULSAR::mesh				*mesh = (PULSAR::mesh*)&PULSAR::STD_CUBE_MESH;
//
//		static PULSAR::VERT_SHADER	vs;
//		static PULSAR::FRAG_SHADER	fs;
//
//		static PULSAR::INPUT_LAYOUT		input_layout;
//		static PULSAR::SAMPLER			sampler;
//
//		PULSAR::TRANSFORM	transform;
//
//
//		void	copy_assign(const PULSAR::SKYBOX &s);
//
//	public:
//		SKYBOX		&operator=(const SKYBOX &s);
//		SKYBOX(const SKYBOX &s);
//		SKYBOX();
//
//		void	set_material(const PULSAR::SKYBOX_MATERIAL &mat);
//		void	set_material(PULSAR::SKYBOX_MATERIAL *mat);
//		void	set_mesh(const PULSAR::mesh &mesh);
//		void	set_mesh(PULSAR::mesh *mesh);
//
//		void	draw()
//		{
//			if (!this->mesh || !this->material)
//				return;
//
//			this->transform.bind(PULSAR::BIND_SCOPE::LOCAL);
//			this->material->bind(PULSAR::BIND_SCOPE::LOCAL);
//
//			PULSAR::SKYBOX::vs.bind(PULSAR::BIND_SCOPE::LOCAL);
//			PULSAR::SKYBOX::fs.bind(PULSAR::BIND_SCOPE::LOCAL);
//			PULSAR::SKYBOX::sampler.bind(PULSAR::BIND_SCOPE::LOCAL);
//			PULSAR::SKYBOX::input_layout.bind(PULSAR::BIND_SCOPE::LOCAL);
//
//			PULSAR::STD_FRONT_FACE_CULL_RS.bind(PULSAR::BIND_SCOPE::LOCAL);
//			this->mesh->bind(PULSAR::BIND_SCOPE::LOCAL);
//			PULSAR::GFX::draw_indexed(this->mesh->get_index_count());
//
//			PULSAR::BINDABLE::unbind_local();
//		}
//	};
//}
