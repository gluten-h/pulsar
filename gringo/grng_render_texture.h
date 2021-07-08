#pragma once

#include "grng_bindable.h"


class grng_render_texture : public GRNG_BINDABLE
{
private:
	ID3D11RenderTargetView		*texture_rtv = NULL;
	ID3D11ShaderResourceView	*texture_srv = NULL;
	UINT						slot = 0u;


	void						set_rt_memory(ID3D11Texture2D *texture);

	void						remove_rtv();
	void						remove_srv();
	void						remove_rt_memory();

	void						copy_assign(const grng_render_texture &rt);

public:
	grng_render_texture			&operator=(const grng_render_texture &rt);
	grng_render_texture(const grng_render_texture &rt);
	grng_render_texture();
	grng_render_texture(ID3D11Texture2D *texture, UINT slot = 0u);
	~grng_render_texture();

	void						set(ID3D11Texture2D *texture);
	void						set_slot(UINT slot);

	ID3D11RenderTargetView		*get_render_target();
	ID3D11ShaderResourceView	*get_shader_resource();

	static GRNG_BINDABLE		*create_manager_ptr();


	void		bind_as_rtv(ID3D11DepthStencilView *depth_stencil_view)
	{
		this->device_context->OMSetRenderTargets(1u, &this->texture_rtv, depth_stencil_view);
	}

	void		bind() override
	{
		this->device_context->PSSetShaderResources(this->slot, 1u, &this->texture_srv);
	}
};

using GRNG_RENDER_TEXTURE = grng_render_texture;
