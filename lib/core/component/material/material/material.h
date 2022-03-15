#pragma once

#include "material_def.h"
#include "component.h"
#include "def_textures.h"
#include "frag_const_buffer.h"
#include "frag_dynamic_const_buffer.h"


namespace PULSAR
{
	class MATERIAL : public PULSAR::COMPONENT
	{
	private:
		PULSAR::DCB::buffer					m_dcb_buffer;
		PULSAR::frag_dynamic_const_buffer	m_cbuffer;

	private:
		PULSAR::TEXTURE	m_albedo_map = PULSAR::STD_QUAD_WHITE_TEX;
		PULSAR::TEXTURE	m_normal_map = PULSAR::STD_QUAD_NORMAL_TEX;
		PULSAR::TEXTURE	m_roughness_map = PULSAR::STD_QUAD_WHITE_TEX;
		PULSAR::TEXTURE	m_metalness_map = PULSAR::STD_QUAD_WHITE_TEX;
		PULSAR::TEXTURE m_ao_map = PULSAR::STD_QUAD_WHITE_TEX;
		PULSAR::TEXTURE	m_exposure_map = PULSAR::STD_QUAD_WHITE_TEX;

		//PULSAR::TEXTURE	*mp_irradiance_map = (PULSAR::TEXTURE*)&PULSAR::STD_QUAD_WHITE_TEX;


		void	set_tex_bind_slots()
		{
			this->m_albedo_map.set_slot(MATERIAL_ALBEDO_MAP_SLOT);
			this->m_normal_map.set_slot(MATERIAL_NORMAL_MAP_SLOT);
			this->m_roughness_map.set_slot(MATERIAL_ROUGHNESS_MAP_SLOT);
			this->m_metalness_map.set_slot(MATERIAL_METALNESS_MAP_SLOT);
			this->m_ao_map.set_slot(MATERIAL_AO_MAP_SLOT);
			this->m_exposure_map.set_slot(MATERIAL_EXPOSURE_MAP_SLOT);
		}

	public:
		MATERIAL	&operator=(const MATERIAL &m) = delete;
		MATERIAL(const MATERIAL &m) = delete;
		MATERIAL() : PULSAR::COMPONENT()
		{
			this->type = PULSAR::COMPONENT_TYPE::MATERIAL;

			PULSAR::DCB::raw_layout raw;
			raw.add<PULSAR::DCB::Float3>(MATERIAL_DCB_ALBEDO_COLOR);
			raw.add<PULSAR::DCB::Bool>(MATERIAL_DCB_ALBEDO_MAP_SRGB);
			raw.add<PULSAR::DCB::Float>(MATERIAL_DCB_NORMAL_FACTOR);
			raw.add<PULSAR::DCB::Float>(MATERIAL_DCB_ROUGHNESS);
			raw.add<PULSAR::DCB::Float>(MATERIAL_DCB_METALNESS);
			raw.add<PULSAR::DCB::Float>(MATERIAL_DCB_AO);
			raw.add<PULSAR::DCB::Float>(MATERIAL_DCB_EXPOSURE);

			this->m_dcb_buffer.set_layout(std::move(raw));
			this->m_dcb_buffer[MATERIAL_DCB_ALBEDO_COLOR] = XMFLOAT3(1.0f, 1.0f, 1.0f);
			this->m_dcb_buffer[MATERIAL_DCB_ALBEDO_MAP_SRGB] = true;
			this->m_dcb_buffer[MATERIAL_DCB_NORMAL_FACTOR] = 1.0f;
			this->m_dcb_buffer[MATERIAL_DCB_ROUGHNESS] = 1.0f;
			this->m_dcb_buffer[MATERIAL_DCB_METALNESS] = 1.0f;
			this->m_dcb_buffer[MATERIAL_DCB_AO] = 0.0f;
			this->m_dcb_buffer[MATERIAL_DCB_EXPOSURE] = 1.0f;

			this->m_cbuffer.set_dcb_buffer(&this->m_dcb_buffer);
		}

		static MATERIAL		*create()
		{
			return ((PULSAR::MATERIAL*)PULSAR::COMPONENT::add_to_manager(new PULSAR::MATERIAL));
		}

		void		bind(PULSAR::BIND_SCOPE scope)
		{
			if (this->m_cbuffer.is_modified())
				this->m_cbuffer.update();
			this->m_cbuffer.bind(scope);

			this->set_tex_bind_slots();
			this->m_albedo_map.bind(scope);
			this->m_normal_map.bind(scope);
			this->m_roughness_map.bind(scope);
			this->m_metalness_map.bind(scope);
			this->m_ao_map.bind(scope);
			this->m_exposure_map.bind(scope);

			XMFLOAT3 albedo_color = this->m_dcb_buffer[MATERIAL_DCB_ALBEDO_COLOR];
			bool albedo_srgb = this->m_dcb_buffer[MATERIAL_DCB_ALBEDO_MAP_SRGB];
			float normal_factor = this->m_dcb_buffer[MATERIAL_DCB_NORMAL_FACTOR];
			float roughness = this->m_dcb_buffer[MATERIAL_DCB_ROUGHNESS];
			float metalness = this->m_dcb_buffer[MATERIAL_DCB_METALNESS];
			float ao = this->m_dcb_buffer[MATERIAL_DCB_AO];
			float exposure = this->m_dcb_buffer[MATERIAL_DCB_EXPOSURE];
		}


		PULSAR::TEXTURE					&albedo_map();
		PULSAR::DCB::layout_elem_ref	albedo_color();
		PULSAR::DCB::layout_elem_ref	albedo_map_srgb();
		PULSAR::TEXTURE					&normal_map();
		PULSAR::DCB::layout_elem_ref	normal_factor();
		PULSAR::TEXTURE					&roughness_map();
		PULSAR::DCB::layout_elem_ref	roughness();
		PULSAR::TEXTURE					&metalness_map();
		PULSAR::DCB::layout_elem_ref	metalness();
		PULSAR::TEXTURE					&ao_map();
		PULSAR::DCB::layout_elem_ref	ao();
		PULSAR::TEXTURE					&exposure_map();
		PULSAR::DCB::layout_elem_ref	exposure();
	};
}
