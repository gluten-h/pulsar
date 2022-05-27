
#include "render_system.h"
#include "ecs/registry.h"
#include "transform/transform_component.h"
#include "mesh/mesh_component.h"
#include "material/material_component.h"
#include "render_queue/render_queue.h"


pulsar::render_system::render_system(pulsar::ecs::registry *registry) : pulsar::ecs::system(registry)
{

}

void	pulsar::render_system::execute(float delta_time)
{
	pulsar::render_queue::instance().clear();
	pulsar::ecs::group group = this->mp_registry->group<pulsar::transform_component, pulsar::mesh_component, pulsar::material_component>();

	for (auto entity : group)
	{
		pulsar::transform &transform = this->mp_registry->get<pulsar::transform_component>(entity).transform;
		pulsar::mesh *mesh = this->mp_registry->get<pulsar::mesh_component>(entity).mesh;
		auto &rq_materials = this->mp_registry->get<pulsar::material_component>(entity).rq_materials;

		int mode = -1;
		while (++mode < pulsar::RENDERING_MODE::RENDERING_MODES_COUNT)
		{
			if (rq_materials[mode])
				pulsar::render_queue::instance().add_job((pulsar::RENDERING_MODE)mode, pulsar::job(&transform, mesh, rq_materials[mode]));
		}
	}
}
