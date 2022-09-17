
#include "viewport_render_system.h"
#include "node/node.h"
#include "metadata/metadata_component.h"
#include "camera/camera_component.h"
#include "transform/transform_component.h"
#include "mesh/mesh_component.h"
#include "material/material_component.h"
#include "renderer/renderer.h"


void	pulsar::viewport_render_system::execute(pulsar::ecs::registry &registry, float delta_time)
{
	pulsar::node *main_camera = pulsar::scene::get_active_scene()->get_main_camera();
	if (!main_camera)
		return;
	pulsar::metadata_component &camera_metadata = main_camera->get_component<pulsar::metadata_component>();

	pulsar::viewport_rq &viewport_rq = pulsar::renderer::instance().viewport_rq();
	viewport_rq.clear();

	auto view = registry.view<pulsar::metadata_component, pulsar::transform_component, pulsar::mesh_component, pulsar::material_component>();
	for (auto entity : view)
	{
		pulsar::metadata_component &metadata = view.get<pulsar::metadata_component>(entity);
		if (!(metadata.mask.viewport & camera_metadata.mask.viewport))
			continue;

		pulsar::transform &transform = view.get<pulsar::transform_component>(entity).transform;
		pulsar::mesh *mesh = view.get<pulsar::mesh_component>(entity).mesh;
		auto &rq_materials = view.get<pulsar::material_component>(entity).rq_materials;

		for (pulsar::rq_material &mat : rq_materials)
			viewport_rq.submit_job(mat.mode, pulsar::viewport_job(&transform, mesh, mat.material));
	}
}
