
#include "camera.h"


namespace pulsar
{
	class perspective_camera : public pulsar::camera
	{
	public:
		perspective_camera &operator=(const perspective_camera&) = default;
		perspective_camera &operator=(perspective_camera&&) = default;
		perspective_camera(const perspective_camera&) = default;
		perspective_camera(perspective_camera&&) = default;
		perspective_camera() = default;
		perspective_camera(const XMMATRIX &projection);
		~perspective_camera() = default;
	};
}
