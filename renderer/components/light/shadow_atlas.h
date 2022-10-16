#pragma once

#include "gfx_resources/render_texture.h"
#include "gfx_resources/depth_stencil_view.h"
#include "utils/singleton.h"
#include <vector>


namespace pulsar
{
	class shadow_atlas : public pulsar::singleton<shadow_atlas>
	{
	private:
		pulsar::render_texture m_rt;
		pulsar::depth_stencil_view m_dsv;

		std::vector<D3D11_RECT> m_available_tiles;

	public:
		shadow_atlas &operator=(const shadow_atlas&) = delete;
		shadow_atlas &operator=(shadow_atlas&&) = delete;
		shadow_atlas(const shadow_atlas&) = delete;
		shadow_atlas(shadow_atlas&&) = delete;
		shadow_atlas();
		~shadow_atlas() = default;

		D3D11_RECT	insert(UINT width, UINT height);
		void	free(D3D11_RECT *rect);
		void	clear(D3D11_RECT *rect);

		void	set_slot(UINT slot);

		void	bind_srv();
		void	bind_rtv();

		void	unbind_srv();
		void	unbind_rtv();
	};
}
