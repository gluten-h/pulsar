
#include "shadow_mapping_pass.h"
#include "config/config.h"
#include "exceptions/rg_exception.h"
#include "gfx_resources/depth_stencil_state.h"
#include "gfx_resources/vert_shader.h"
#include "gfx_resources/frag_shader.h"
#include "gfx_resources/input_layout.h"
#include "config/rasterizer_state.h"
#include "renderer/renderer.h"
#include "rq/shadows_rq.h"
#include "light/point_shadow_map.h"
#include "scene/scene.h"
#include "metadata/metadata_component.h"
#include "transform/transform_component.h"
#include "mesh/mesh_component.h"
#include "material/material_component.h"
#include "light/light_component.h"


pulsar::shadow_mapping_pass::shadow_mapping_pass(const std::string &name) : pulsar::rg::pass(name)
{
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	this->mp_dss = new pulsar::depth_stencil_state(TRUE, D3D11_COMPARISON_LESS, D3D11_DEPTH_WRITE_MASK_ALL);
	this->mp_shadow_mapping_vs = new pulsar::vert_shader(pulsar::SHADOW_MAPPING_VS_PATH);
	this->mp_shadow_mapping_fs = new pulsar::frag_shader(pulsar::SHADOW_MAPPING_FS_PATH);
	this->mp_input_layout = new pulsar::input_layout(this->mp_shadow_mapping_vs->blob(), ied, (UINT)std::size(ied));

	this->mp_shadows_rq_input = new pulsar::rg::async_input<pulsar::shadows_rq>(pulsar::RG_G_SHADOWS_RQ, this->mp_shadows_rq);
	this->mp_shadows_rq_source = new pulsar::rg::async_source<pulsar::shadows_rq>(pulsar::RG_G_SHADOWS_RQ, this->mp_shadows_rq);

	this->register_input(this->mp_shadows_rq_input);
	this->register_source(this->mp_shadows_rq_source);
}

pulsar::shadow_mapping_pass::~shadow_mapping_pass()
{
	delete this->mp_dss;
	delete this->mp_shadow_mapping_vs;
	delete this->mp_shadow_mapping_fs;
	delete this->mp_input_layout;

	delete this->mp_shadows_rq_input;
	delete this->mp_shadows_rq_source;
}

void	pulsar::shadow_mapping_pass::validate() const
{
	if (!this->mp_shadows_rq)
		THROW_RG_EXC("Shadows RQ isn't bound");
}

void	pulsar::shadow_mapping_pass::execute()
{
	pulsar::renderer &renderer = pulsar::renderer::instance();
	pulsar::scene *active_scene = pulsar::scene::get_active_scene();

	if (!active_scene)
		return;

	pulsar::ecs::registry &registry = active_scene->registry();

	auto &submitted_lights = *renderer.get_submitted_lights();
	auto view = registry.view<pulsar::metadata_component, pulsar::transform_component, pulsar::mesh_component, pulsar::material_component>();

	int i = -1;
	while (++i < submitted_lights.size())
	{
		pulsar::ecs::entity light_entity = submitted_lights[i];

		uint32_t light_mask = registry.get<pulsar::metadata_component>(light_entity).mask.shadows;
		pulsar::transform *light_transform = &registry.get<pulsar::transform_component>(light_entity).transform;
		pulsar::shadow_map *shadow_map = registry.get<pulsar::light_component>(light_entity).light->shadow_map();

		shadow_map->clear();
		this->mp_shadows_rq->clear();

		for (auto entity : view)
		{
			uint32_t mask = view.get<pulsar::metadata_component>(entity).mask.shadows;
			if (!(mask & light_mask))
				continue;

			pulsar::transform &transform = view.get<pulsar::transform_component>(entity).transform;
			pulsar::mesh *mesh = view.get<pulsar::mesh_component>(entity).mesh;
			auto &rq_materials = view.get<pulsar::material_component>(entity).rq_materials;

			for (pulsar::rq_material &mat : rq_materials)
				this->mp_shadows_rq->submit_job(mat.mode, pulsar::shadows_job(&transform, mesh));
		}

		{
			pulsar::BACK_FACE_CULL_RS.bind();
			this->mp_dss->bind();
			this->mp_shadow_mapping_vs->bind();
			this->mp_shadow_mapping_fs->bind();
			this->mp_input_layout->bind();

			int i = -1;
			while (++i < shadow_map->draw_calls())
			{
				shadow_map->bind_rtv(i, light_transform);
				this->mp_shadows_rq->execute();
				shadow_map->unbind_rtv();
			}
		}

		{
			this->mp_input_layout->unbind();
			this->mp_shadow_mapping_fs->unbind();
			this->mp_shadow_mapping_vs->unbind();
			this->mp_dss->unbind();
			pulsar::BACK_FACE_CULL_RS.unbind();
		}
	}
}
