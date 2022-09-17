#pragma once

#include "gfx_resources/shader_texture.h"
#include "gfx_resources/cubemap.h"
#include "gfx_resources/frag_dynamic_cbuffer.h"


namespace pulsar
{
	class frag_shader;

	class material
	{
	private:
		pulsar::dcb::buffer m_dcb_buffer;
		pulsar::frag_dynamic_cbuffer m_cbuffer;

		pulsar::frag_shader const *mp_shader = NULL;

		pulsar::shader_texture m_albedo_map;
		pulsar::shader_texture m_normal_map;
		pulsar::shader_texture m_roughness_map;
		pulsar::shader_texture m_metalness_map;
		pulsar::shader_texture m_ao_map;
		pulsar::shader_texture m_exposure_map;
		pulsar::cubemap m_irradiance_map;

	private:
		void	set_tex_bind_slots();

	public:
		material &operator=(const material&) = delete;
		material &operator=(material&&) = delete;
		material(const material&) = delete;
		material(material&&) = delete;
		material();
		~material() = default;

		void	set_shader(pulsar::frag_shader *shader);
		void	bind();
		void	unbind();

		pulsar::shader_texture			&albedo_map();
		pulsar::dcb::layout_elem_ref	albedo_color();
		pulsar::dcb::layout_elem_ref	albedo_map_srgb();
		pulsar::shader_texture			&normal_map();
		pulsar::dcb::layout_elem_ref	normal_factor();
		pulsar::shader_texture			&roughness_map();
		pulsar::dcb::layout_elem_ref	roughness();
		pulsar::shader_texture			&metalness_map();
		pulsar::dcb::layout_elem_ref	metalness();
		pulsar::shader_texture			&ao_map();
		pulsar::dcb::layout_elem_ref	ao();
		pulsar::shader_texture			&exposure_map();
		pulsar::dcb::layout_elem_ref	exposure();
		pulsar::cubemap					&irradiance_map();
		pulsar::dcb::layout_elem_ref	irradiance_color();
	};
}
