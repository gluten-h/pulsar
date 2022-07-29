#pragma once

#include "texture_resource.h"
#include "sync_resource.h"


namespace pulsar
{
	class framebuffer : public pulsar::texture_resource, public pulsar::sync_resource
	{
	private:
		IDXGISwapChain *mp_swap_chain = NULL;
		ID3D11RenderTargetView *mp_rtv = NULL;

		void	create_framebuffer(HWND hwnd, BOOL windowed);
		void	destroy_framebuffer();

	protected:
		void	resize_resource(UINT width, UINT height) override;

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

		void	clear();
		void	present() const;

		void	bind(ID3D11DepthStencilView *dsv = NULL) const;
		void	unbind() const;
	};
}
