#pragma once

#include "texture_resource.h"
#include "sync_resource.h"


namespace pulsar
{
	class depth_stencil_view : public pulsar::texture_resource, public pulsar::sync_resource
	{
	private:
		ID3D11DepthStencilView *mp_dsv = NULL;

		void	create_dsv(UINT width, UINT height);
		void	destroy_dsv();

	protected:
		void	resize_resource(UINT width, UINT height) override;

	public:
		depth_stencil_view &operator=(const depth_stencil_view &) = delete;
		depth_stencil_view &operator=(depth_stencil_view&&) = delete;
		depth_stencil_view(const depth_stencil_view &) = delete;
		depth_stencil_view(depth_stencil_view&&) = delete;
		depth_stencil_view() = default;
		depth_stencil_view(UINT width, UINT height);
		~depth_stencil_view();

		void	clear();
		void	clear(D3D11_RECT *rect);

		ID3D11DepthStencilView	*dsv();
	};

	using dsv = pulsar::depth_stencil_view;
}
