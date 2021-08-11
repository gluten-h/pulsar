#pragma once

#include "grng_bindable.h"
#include "grng_bindable_entity.h"


class grng_render_texture : public GRNG_BINDABLE
{
private:
	ID3D11RenderTargetView		*texture_rtv = NULL;
	ID3D11ShaderResourceView	*texture_srv = NULL;
	UINT						slot = 0u;

	GRNG_BIND_MODE						mode = GRNG_BIND_MODE::SRV;
	mutable ID3D11DepthStencilView		*ds_view = NULL;


	void						set_rt_memory(ID3D11Texture2D *texture);

	void						remove_rtv();
	void						remove_srv();
	void						remove_rt_memory();

	void						copy_assign(const grng_render_texture &rt);

protected:
	void		remove_from_entities() override
	{
		for (auto &it : this->entities)
			it->_remove_bindable_ignore_entity(this);
		this->entities.clear();
	}

public:
	using GRNG_BINDABLE::bind;

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

	void		set_mode(GRNG_BIND_MODE mode);
	void		set_ds_view(ID3D11DepthStencilView *ds_view);

	static grng_render_texture		*create();

	void		clear();

	void		bind() const override;
	void		unbind() const override;
};

using GRNG_RENDER_TEXTURE = grng_render_texture;
