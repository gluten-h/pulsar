#pragma once

#include "utils/math.h"
#include "config/config.h"
#include "dynamic_const_buffers/vert_dynamic_const_buffer.h"


namespace pulsar
{
	struct vert_camera
	{
		XMMATRIX view;
		XMMATRIX proj;
	};
	struct frag_camera
	{
		XMFLOAT3 pos;
		float gamma;

		XMFLOAT3 dir;
		float exposure;
	};

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
		const XMMATRIX	&get_projection() const;
	};
}
