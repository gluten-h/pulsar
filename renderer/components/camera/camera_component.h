
#include "camera.h"


namespace PULSAR
{
	struct camera_component
	{
		PULSAR::camera *camera = NULL;

		camera_component() = default;
		camera_component(PULSAR::camera *camera)
		{
			this->camera = camera;
		}
		~camera_component() = default;

		operator PULSAR::camera *()
		{
			return (this->camera);
		}
	};
}
