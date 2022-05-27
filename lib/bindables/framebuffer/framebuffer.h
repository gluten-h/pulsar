#pragma once

#include "bindable/bindable.h"
#include "bindable/buffer_resource.h"


namespace pulsar
{
	class framebuffer : public pulsar::bindable, public pulsar::buffer_resource
	{
	private:
		IDXGISwapChain *mp_swap_chain = NULL;
		ID3D11RenderTargetView *mp_render_target = NULL;

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
		XMUINT2	size() const;

		void	resize(UINT width, UINT height) override;
		void	clear() override;
		void	present() const;

		void	bind(ID3D11DepthStencilView *mp_ds_view = NULL) const;
		void	unbind() const;
	};
}
