#pragma once

#include "texture2d_resource.h"
#include "sync_resource.h"


namespace pulsar
{
	class render_texture : public pulsar::texture2d_resource, public pulsar::sync_resource
	{
	private:
		ID3D11RenderTargetView *mp_rtv = NULL;
		ID3D11ShaderResourceView *mp_srv = NULL;
		UINT m_slot = 0u;

		void	create_rt(UINT width, UINT height, DXGI_FORMAT format);
		void	destroy_rt();

	protected:
		void	resize_resource(UINT width, UINT height) override;

	public:
		render_texture &operator=(const render_texture&) = delete;
		render_texture &operator=(render_texture&&) = delete;
		render_texture(const render_texture&) = delete;
		render_texture(render_texture&&) = delete;
		render_texture() = default;
		render_texture(UINT width, UINT height, DXGI_FORMAT format, UINT slot = 0u);
		~render_texture();

		ID3D11RenderTargetView	*rtv();
		ID3D11ShaderResourceView	*srv();

		void	set(UINT width, UINT height, DXGI_FORMAT format);
		void	set_slot(UINT slot);

		void	clear();
		void	clear(float *clear_color);
		void	clear(D3D11_RECT *rect);
		void	clear(D3D11_RECT *rect, float *clear_color);

		void	bind_srv() const;
		void	bind_rtv(ID3D11DepthStencilView *dsv = NULL) const;

		void	unbind_srv() const;
		void	unbind_rtv() const;
	};
}
