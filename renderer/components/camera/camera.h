
#include "utils/math.h"
#include "config/camera.h"
#include "dynamic_const_buffers/vert_dynamic_const_buffer.h"


namespace PULSAR
{
	class camera
	{
	private:
		XMMATRIX m_projection = XMMatrixIdentity();;

	protected:
		camera &operator=(const camera&) = default;
		camera &operator=(camera&&) = default;
		camera(const camera&) = default;
		camera(camera&&) = default;
		camera() = default;
		camera(const XMMATRIX &projection);
		~camera() = default;

	public:
		const XMMATRIX	&projection() const;
	};
}
