#pragma once

#include "shadow_map.h"
#include "utils/math.h"
#include "gfx_resources/viewport.h"
#include "gfx_resources/vert_cbuffer.h"


namespace pulsar
{
	class point_shadow_map : public pulsar::shadow_map
	{
		struct shadow_transform
		{
			XMFLOAT4X4 view;
			XMFLOAT4X4 proj;
		};

		struct view_specs
		{
			XMFLOAT3 dir;
			XMFLOAT3 up;
		};

	private:
		D3D11_RECT m_rects[6u];
		pulsar::viewport m_viewports[6u];
		XMFLOAT4 m_uvs[6u];

		float m_z_near = 0.0f;
		float m_z_far = 0.0f;

		view_specs m_view_specs[6u];
		XMFLOAT4X4 m_view;
		XMFLOAT4X4 m_proj;
		pulsar::vert_cbuffer<XMFLOAT4X4> m_view_cbuffer;
		pulsar::vert_cbuffer<XMFLOAT4X4> m_proj_cbuffer;

		void	create_shadow_map(UINT width, UINT height);
		void	destroy_shadow_map();

	public:
		point_shadow_map &operator=(const point_shadow_map&) = delete;
		point_shadow_map &operator=(point_shadow_map&&) = delete;
		point_shadow_map(const point_shadow_map&) = delete;
		point_shadow_map(point_shadow_map&&) = delete;
		point_shadow_map();
		~point_shadow_map();

		void	set(UINT width, UINT height, float z_near = 0.001f, float z_far = 1000.0f) override;

		void	clear() override;
		uint8_t	draw_calls() const override;
		XMFLOAT4	uv(uint8_t id) const override;

		void	bind_rtv(uint8_t id, const pulsar::transform *transform) override;
		void	bind_srv() override;

		void	unbind_rtv() override;
		void	unbind_srv() override;
	};
}
