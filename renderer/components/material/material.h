#pragma once

#include "config/shader.h"
#include "shader_texture/shader_texture.h"
#include "dynamic_const_buffers/frag_dynamic_const_buffer.h"


namespace PULSAR
{
	class frag_shader;

	class material
	{
	private:
		PULSAR::dcb::buffer m_dcb_buffer;
		PULSAR::frag_dynamic_const_buffer m_cbuffer;

		PULSAR::frag_shader const *mp_shader = NULL;

		PULSAR::shader_texture m_albedo_map;
		PULSAR::shader_texture m_normal_map;
		PULSAR::shader_texture m_roughness_map;
		PULSAR::shader_texture m_metalness_map;
		PULSAR::shader_texture m_ao_map;
		PULSAR::shader_texture m_exposure_map;

		//PULSAR::shader_texture	*mp_irradiance_map = (PULSAR::shader_texture*)&PULSAR::STD_QUAD_WHITE_TEX;

	private:
		void	set_tex_bind_slots();

	public:
		material &operator=(const material&) = delete;
		material &operator=(material&&) = delete;
		material(const material&) = delete;
		material(material&&) = delete;
		material();
		~material() = default;

		void	set_shader(PULSAR::frag_shader *shader);
		void	bind();

		PULSAR::shader_texture			&albedo_map();
		PULSAR::dcb::layout_elem_ref	albedo_color();
		PULSAR::dcb::layout_elem_ref	albedo_map_srgb();
		PULSAR::shader_texture			&normal_map();
		PULSAR::dcb::layout_elem_ref	normal_factor();
		PULSAR::shader_texture			&roughness_map();
		PULSAR::dcb::layout_elem_ref	roughness();
		PULSAR::shader_texture			&metalness_map();
		PULSAR::dcb::layout_elem_ref	metalness();
		PULSAR::shader_texture			&ao_map();
		PULSAR::dcb::layout_elem_ref	ao();
		PULSAR::shader_texture			&exposure_map();
		PULSAR::dcb::layout_elem_ref	exposure();
	};
}
