
#include "perspective_camera.h"
#include "ecs/ecs.h"
#include "config/config.h"
#include "metadata/metadata_component.h"


namespace pulsar
{
	struct camera_component
	{
		pulsar::camera *camera = NULL;

		float gamma = 2.2f;
		float exposure = 1.0f;

		camera_component() = default;
		camera_component(pulsar::camera *camera)
		{
			this->camera = camera;
		}
		~camera_component() = default;

		void	on_construct(pulsar::ecs::registry &registry, pulsar::ecs::entity entity)
		{
			pulsar::metadata_component &metadata = registry.get<pulsar::metadata_component>(entity);
			metadata.mask.viewport = pulsar::DEFAULT_CAMERA_VIEWPORT_MASK;
		}
	};
}
