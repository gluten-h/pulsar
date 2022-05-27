#pragma once

#include "cubemap/cubemap.h"
#include "dynamic_const_buffers/frag_dynamic_const_buffer.h"


namespace pulsar
{
	class skybox_material
	{
	private:
		pulsar::dcb::buffer m_dcb_buffer;
		pulsar::frag_dynamic_const_buffer m_cbuffer;

		pulsar::cubemap m_albedo_map;
		pulsar::cubemap m_exposure_map;

		void	set_tex_bind_slots();

	public:
		skybox_material &operator=(const skybox_material&) = delete;
		skybox_material &operator=(skybox_material&&) = delete;
		skybox_material(const skybox_material&) = delete;
		skybox_material(skybox_material&&) = delete;
		skybox_material();
		~skybox_material() = default;

		void	bind();
		void	unbind();

		pulsar::cubemap					&albedo_map();
		pulsar::dcb::layout_elem_ref	albedo_color();
		pulsar::dcb::layout_elem_ref	albedo_map_srgb();
		pulsar::cubemap					&exposure_map();
		pulsar::dcb::layout_elem_ref	exposure();
	};
}
