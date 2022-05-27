
#include "perspective_camera.h"


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
	};
}
