#pragma once

#include "grng_bindable.h"


class grng_render_target : public GRNG_BINDABLE
{
private:
	friend class grng_manager_ptr;

private:
	IDXGISwapChain					*swap_chain = NULL;
	ID3D11Texture2D					*back_buffer_texture = NULL;
	ID3D11RenderTargetView			*back_buffer = NULL;


	void		set_rt_memory(HWND hwnd, BOOL windowed);

	void		remove_swap_chain();
	void		remove_back_buffer_texture();
	void		remove_back_buffer();
	void		remove_rt_memory();

	void		copy_assign(const grng_render_target &rt);

	static GRNG_BINDABLE		*create_manager_ptr();

public:
	grng_render_target			&operator=(const grng_render_target &rt);
	grng_render_target(const grng_render_target &rt);
	grng_render_target();
	grng_render_target(HWND hwnd, BOOL windowed = TRUE);
	~grng_render_target();

	void		set(HWND hwnd, BOOL windowed = TRUE);

	void		clear();
	void		present();

	void		bind() const override;
	void		bind(ID3D11DepthStencilView *ds_view) const;
};

using GRNG_RENDER_TARGET = grng_render_target;
