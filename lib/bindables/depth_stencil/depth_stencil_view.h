#pragma once

#include "bindable/bindable.h"
#include "bindable/buffer_resource.h"


namespace PULSAR
{
	class depth_stencil_view : public PULSAR::bindable, public PULSAR::buffer_resource
	{
	private:
		ID3D11Texture2D *mp_texture = NULL;
		ID3D11DepthStencilView *mp_ds_view = NULL;

	private:
		void	create_ds_view(float width, float height);
		void	free();

	public:
		depth_stencil_view &operator=(const depth_stencil_view &) = delete;
		depth_stencil_view &operator=(depth_stencil_view&&) = delete;
		depth_stencil_view(const depth_stencil_view &) = delete;
		depth_stencil_view(depth_stencil_view&&) = delete;
		depth_stencil_view() = default;
		depth_stencil_view(float width, float height);
		~depth_stencil_view();

		void	set(float width, float height);
		ID3D11Texture2D	*get_texture();
		ID3D11DepthStencilView	*get_view();

		void	resize(UINT width, UINT height) override;
		void	clear() override;

		void	bind() const override;
		void	unbind() const override;
	};

	using ds_view = depth_stencil_view;
}
