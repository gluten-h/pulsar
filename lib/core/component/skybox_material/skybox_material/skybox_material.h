//#pragma once
//
//#include "component.h"
//#include "skybox_material_def.h"
//#include "skybox_material_shader.h"
//#include "def_cubemaps.h"
//#include "frag_const_buffer.h"
//#include "gfx.h"
//
//
//namespace PULSAR
//{
//	class SKYBOX_MATERIAL : public PULSAR::COMPONENT
//	{
//	private:
//		static PULSAR::SKYBOX_MATERIAL_SHADER								skybox_mat_shader;
//		static PULSAR::FRAG_CONST_BUFFER<PULSAR::SKYBOX_MATERIAL_SHADER>	skybox_mat_cbuffer;
//
//	public:
//		PULSAR::CUBEMAP		env_map = STD_CUBEMAP_BLACK;
//		XMFLOAT3			env_map_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
//		bool				env_map_srgb = true;
//
//		CUBEMAP		exposure_map = STD_CUBEMAP_WHITE;
//		float		exposure = 1.0f;
//
//
//		SKYBOX_MATERIAL &operator=(const SKYBOX_MATERIAL &m) = delete;
//		SKYBOX_MATERIAL(const SKYBOX_MATERIAL &m) = delete;
//		SKYBOX_MATERIAL() : PULSAR::COMPONENT()
//		{
//			this->type = PULSAR::COMPONENT_TYPE::SKYBOX_MATERIAL;
//			this->env_map.set_slot(SKYBOX_MATERIAL_ENV_MAP_SLOT);
//			this->exposure_map.set_slot(SKYBOX_MATERIAL_EXPOSURE_MAP_SLOT);
//		}
//
//		static SKYBOX_MATERIAL		*create()
//		{
//			return ((PULSAR::SKYBOX_MATERIAL*)PULSAR::COMPONENT::add_to_manager(new PULSAR::SKYBOX_MATERIAL));
//		}
//
//		void		bind(PULSAR::BIND_SCOPE scope)
//		{
//			PULSAR::SKYBOX_MATERIAL::skybox_mat_shader.env_map_color = this->env_map_color;
//			PULSAR::SKYBOX_MATERIAL::skybox_mat_shader.env_map_srgb = this->env_map_srgb;
//			PULSAR::SKYBOX_MATERIAL::skybox_mat_shader.cam_gamma = PULSAR::GFX::get_curr_camera()->get_gamma();
//			PULSAR::SKYBOX_MATERIAL::skybox_mat_shader.exposure = this->exposure;
//
//			PULSAR::SKYBOX_MATERIAL::skybox_mat_cbuffer.update(PULSAR::SKYBOX_MATERIAL::skybox_mat_shader);
//			PULSAR::SKYBOX_MATERIAL::skybox_mat_cbuffer.bind(scope);
//
//			PULSAR::SKYBOX_MATERIAL::env_map.bind(scope);
//			PULSAR::SKYBOX_MATERIAL::exposure_map.bind(scope);
//		}
//	};
//}
