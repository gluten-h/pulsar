
#include "camera.h"


namespace pulsar
{
	class perspective_camera : public pulsar::camera
	{
	private:
		float m_fov_rad;
		float m_z_near, m_z_far;

	public:
		perspective_camera &operator=(const perspective_camera&) = default;
		perspective_camera &operator=(perspective_camera&&) = default;
		perspective_camera(const perspective_camera&) = default;
		perspective_camera(perspective_camera&&) = default;
		perspective_camera() = default;
		perspective_camera(UINT width, UINT height, float fov_rad, float near_z, float far_z);
		~perspective_camera() = default;

		const XMMATRIX	&get_projection() const override;
	};
}
