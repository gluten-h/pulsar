#pragma once

#include "bindable.h"
#include "bindable_entity.h"


namespace PULSAR
{
	class RENDER_TEXTURE : public PULSAR::BINDABLE
	{
	private:
		ID3D11RenderTargetView		*texture_rtv = NULL;
		ID3D11ShaderResourceView	*texture_srv = NULL;
		UINT						slot = 0u;

		BIND_MODE							mode = BIND_MODE::SRV;
		mutable ID3D11DepthStencilView		*ds_view = NULL;


		void	set_rt_memory(ID3D11Texture2D *texture);

		void	remove_rtv();
		void	remove_srv();
		void	remove_rt_memory();

		void	copy_assign(const RENDER_TEXTURE &rt);

	protected:
		void		remove_from_entities() override
		{
			for (auto &it : this->entities)
				it->_remove_bindable_ignore_entity(this);
			this->entities.clear();
		}

	public:
		using PULSAR::BINDABLE::bind;

	public:
		RENDER_TEXTURE		&operator=(const RENDER_TEXTURE &rt);
		RENDER_TEXTURE(const RENDER_TEXTURE &rt);
		RENDER_TEXTURE();
		RENDER_TEXTURE(ID3D11Texture2D *texture, UINT slot = 0u);
		~RENDER_TEXTURE();

		void	set(ID3D11Texture2D *texture);
		void	set_slot(UINT slot);

		ID3D11RenderTargetView		*get_render_target();
		ID3D11ShaderResourceView	*get_shader_resource();

		void	set_mode(BIND_MODE mode);
		void	set_ds_view(ID3D11DepthStencilView *ds_view);

		static RENDER_TEXTURE	*create();

		void	clear();

		void	bind() const override;
		void	unbind() const override;
	};
}
