#pragma once

#include "utils/math.h"
#include "config/config.h"
#include "gfx_resources/viewport.h"


namespace pulsar
{
	struct vert_camera
	{
		XMFLOAT4X4 view;
		XMFLOAT4X4 proj;
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
		XMFLOAT4X4 m_mat;
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
		const XMFLOAT4X4	&projection() const;
	};
}
