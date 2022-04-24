#pragma once

#include "bindable/bindable.h"
#include "bindable/buffer_resource.h"


namespace PULSAR
{
	class framebuffer : public PULSAR::bindable, public PULSAR::buffer_resource
	{
	private:
		IDXGISwapChain *mp_swap_chain = NULL;
		ID3D11Texture2D *mp_texture = NULL;
		ID3D11RenderTargetView *mp_render_target = NULL;

		mutable ID3D11DepthStencilView *mp_ds_view = NULL;

	private:
		void	create_feamebuffer(HWND hwnd, BOOL windowed);
		void	free();

	public:
		framebuffer &operator=(const framebuffer&) = delete;
		framebuffer &operator=(framebuffer&&) = delete;
		framebuffer(const framebuffer&) = delete;
		framebuffer(framebuffer&&) = delete;
		framebuffer() = default;
		framebuffer(HWND hwnd, BOOL windowed = TRUE);
		~framebuffer();

		void	set(HWND hwnd, BOOL windowed = TRUE);
		ID3D11DepthStencilView	*&ds_view();

		void	clear() override;
		void	present();

		void	bind() const override;
		void	unbind() const override;
	};
}
