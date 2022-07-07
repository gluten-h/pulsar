
#include "viewport_render_system.h"
#include "node/node.h"
#include "metadata/metadata_component.h"
#include "camera/camera_component.h"
#include "transform/transform_component.h"
#include "mesh/mesh_component.h"
#include "material/material_component.h"
#include "render_queue/render_queue.h"


void	pulsar::viewport_render_system::execute(pulsar::ecs::registry &registry, float delta_time)
{
	pulsar::node *main_camera = pulsar::scene::get_active_scene()->get_main_camera();
	if (!main_camera)
		return;
	pulsar::metadata_component &camera_metadata = main_camera->get_component<pulsar::metadata_component>();

	pulsar::render_queue::instance().clear();
	auto view = registry.view<pulsar::metadata_component, pulsar::transform_component, pulsar::mesh_component, pulsar::material_component>();

	for (auto entity : view)
	{
		pulsar::metadata_component &metadata = view.get<pulsar::metadata_component>(entity);
		if (!(metadata.mask.viewport & camera_metadata.mask.viewport))
			continue;

		pulsar::transform &transform = view.get<pulsar::transform_component>(entity).transform;
		pulsar::mesh *mesh = view.get<pulsar::mesh_component>(entity).mesh;
		auto &rq_materials = view.get<pulsar::material_component>(entity).rq_materials;

		int mode = -1;
		while (++mode < pulsar::RENDERING_MODE::RENDERING_MODES_COUNT)
		{
			if (rq_materials[mode])
				pulsar::render_queue::instance().add_job((pulsar::RENDERING_MODE)mode, pulsar::job(&transform, mesh, rq_materials[mode]));
		}
	}
}
