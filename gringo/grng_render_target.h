#pragma once

#include "grng_bindable.h"
#include "grng_bindable_entity.h"


class grng_render_target : public GRNG_BINDABLE, public GRNG_BUFFER_RESOURCE
{
private:
	IDXGISwapChain					*swap_chain = NULL;
	ID3D11Texture2D					*back_buffer_texture = NULL;
	ID3D11RenderTargetView			*back_buffer = NULL;

	mutable ID3D11DepthStencilView	*ds_view = NULL;


	void		set_rt_memory(HWND hwnd, BOOL windowed);

	void		remove_swap_chain();
	void		remove_back_buffer_texture();
	void		remove_back_buffer();
	void		remove_rt_memory();

	void		copy_assign(const grng_render_target &rt);

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
	grng_render_target			&operator=(const grng_render_target &rt);
	grng_render_target(const grng_render_target &rt);
	grng_render_target();
	grng_render_target(HWND hwnd, BOOL windowed = TRUE);
	~grng_render_target();

	void		set(HWND hwnd, BOOL windowed = TRUE);
	void		set_ds_view(ID3D11DepthStencilView *ds_view);

	void		clear() override;
	void		present();

	static grng_render_target	*create();

	void		bind() const override
	{
		this->device_context->OMSetRenderTargets(1u, &this->back_buffer, this->ds_view);
		GRNG_BINDABLE::add_unbind(*this);
	}

	void		unbind() const override
	{
		this->device_context->OMSetRenderTargets(0u, NULL, NULL);
		this->ds_view = NULL;
	}

};

using GRNG_RENDER_TARGET = grng_render_target;
