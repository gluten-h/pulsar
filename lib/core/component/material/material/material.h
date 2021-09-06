#pragma once

#include "component.h"
#include "def_textures.h"
#include "material_shader.h"
#include "frag_const_buffer.h"


namespace PULSAR
{
	class MATERIAL : public PULSAR::COMPONENT
	{
	private:
		static PULSAR::MATERIAL_SHADER								mat_shader;
		static PULSAR::FRAG_CONST_BUFFER<PULSAR::MATERIAL_SHADER>	mat_cbuffer;

	public:
		TEXTURE		albedo_map = PULSAR::STD_QUAD_WHITE_TEX;
		XMFLOAT3	albedo_color = XMFLOAT3(1.0f, 1.0f, 1.0f);
		bool		albedo_map_srgb = true;

		TEXTURE		normal_map = PULSAR::STD_QUAD_NORMAL_TEX;
		float		normal_factor = 1.0f;

		TEXTURE		roughness_map = PULSAR::STD_QUAD_WHITE_TEX;
		float		roughness = 1.0f;

		TEXTURE		metalness_map = PULSAR::STD_QUAD_WHITE_TEX;
		float		metalness = 1.0f;

		TEXTURE		ao_map = PULSAR::STD_QUAD_WHITE_TEX;
		float		ao = 0.0f;

		TEXTURE		exposure_map = PULSAR::STD_QUAD_WHITE_TEX;
		float		exposure = 1.0f;

		TEXTURE		irradiance_map = PULSAR::STD_QUAD_WHITE_TEX;
		float		irradiance = 0.0f;


		MATERIAL	&operator=(const MATERIAL &m) = delete;
		MATERIAL(const MATERIAL &m) = delete;
		MATERIAL() : PULSAR::COMPONENT()
		{
			this->type = PULSAR::COMPONENT_TYPE::MATERIAL;

			this->albedo_map.set_slot(MATERIAL_ALBEDO_MAP_SLOT);
			this->normal_map.set_slot(MATERIAL_NORMAL_MAP_SLOT);
			this->roughness_map.set_slot(MATERIAL_ROUGHNESS_MAP_SLOT);
			this->metalness_map.set_slot(MATERIAL_METALNESS_MAP_SLOT);
			this->ao_map.set_slot(MATERIAL_AO_MAP_SLOT);
			this->exposure_map.set_slot(MATERIAL_EXPOSURE_MAP_SLOT);
		}

		static MATERIAL		*create()
		{
			return ((PULSAR::MATERIAL*)PULSAR::COMPONENT::add_to_manager(new PULSAR::MATERIAL));
		}

		void		bind(PULSAR::BIND_SCOPE scope)
		{
			PULSAR::MATERIAL::mat_shader.albedo_color = this->albedo_color;
			PULSAR::MATERIAL::mat_shader.albedo_map_srgb = this->albedo_map_srgb;
			PULSAR::MATERIAL::mat_shader.normal_factor = this->normal_factor;
			PULSAR::MATERIAL::mat_shader.roughness = this->roughness;
			PULSAR::MATERIAL::mat_shader.metalness = this->metalness;
			PULSAR::MATERIAL::mat_shader.ao = this->ao;
			PULSAR::MATERIAL::mat_shader.exposure = this->exposure;

			PULSAR::MATERIAL::mat_cbuffer.update(PULSAR::MATERIAL::mat_shader);
			PULSAR::MATERIAL::mat_cbuffer.bind(scope);

			this->albedo_map.bind(scope);
			this->normal_map.bind(scope);
			this->roughness_map.bind(scope);
			this->metalness_map.bind(scope);
			this->ao_map.bind(scope);
			this->exposure_map.bind(scope);
		}
	};
}
