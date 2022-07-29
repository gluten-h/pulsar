#pragma once

#include "utils/math.h"
#include "config/config.h"
#include "gfx_resources/viewport.h"


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
	protected:
		pulsar::viewport m_viewport;

		camera &operator=(const camera&) = default;
		camera &operator=(camera&&) = default;
		camera(const camera&) = default;
		camera(camera&&) = default;
		camera() = delete;
		camera(UINT width, UINT height);
		virtual ~camera() = default;

	public:
		pulsar::viewport	&viewport();
		virtual const XMMATRIX	&get_projection() const = 0;
	};
}
