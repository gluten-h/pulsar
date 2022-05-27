#pragma once

#include "bindable/bindable.h"
#include "bindable/buffer_resource.h"


namespace pulsar
{
	class render_texture : public pulsar::bindable, public pulsar::buffer_resource
	{
	private:
		ID3D11Texture2D *mp_texture = NULL;
		ID3D11RenderTargetView *mp_rtv = NULL;
		ID3D11ShaderResourceView *mp_srv = NULL;
		UINT m_slot = 0u;

	private:
		void	create_rt(UINT width, UINT height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags);
		void	free();

	public:
		render_texture &operator=(const render_texture&) = delete;
		render_texture &operator=(render_texture&&) = delete;
		render_texture(const render_texture&) = delete;
		render_texture(render_texture&&) = delete;
		render_texture() = default;
		render_texture(UINT width, UINT height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags, UINT slot = 0u);
		~render_texture();

		void	set(UINT width, UINT height, DXGI_FORMAT format, UINT bind_flags, UINT cpu_access_flags);
		void	set_slot(UINT slot);

		ID3D11RenderTargetView *render_target();
		ID3D11ShaderResourceView *shader_resource();
		XMUINT2	size() const;

		void	resize(UINT width, UINT height) override;
		void	clear() override;

		void	bind_srv() const;
		void	bind_rtv(ID3D11DepthStencilView *ds_view = NULL) const;

		void	unbind_srv() const;
		void	unbind_rtv() const;
	};
}
