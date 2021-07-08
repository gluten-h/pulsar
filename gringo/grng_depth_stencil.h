#pragma once

#include "grng_bindable.h"


class grng_depth_stencil : public GRNG_BINDABLE
{
private:
	ID3D11Texture2D				*ds_texture = NULL;
	ID3D11DepthStencilState		*ds_state = NULL;
	ID3D11DepthStencilView		*ds_view = NULL;


	void						set_ds_memory(float width, float height, D3D11_COMPARISON_FUNC comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask);

	void						remove_ds_texture_memory();
	void						remove_ds_state_memory();
	void						remove_ds_view_memory();
	void						remove_ds_memory();

	void						copy_assign(const grng_depth_stencil &ds);

public:
	grng_depth_stencil			&operator=(const grng_depth_stencil &ds);
	grng_depth_stencil(const grng_depth_stencil &ds);
	grng_depth_stencil();
	grng_depth_stencil(float width, float height, D3D11_COMPARISON_FUNC comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask);
	~grng_depth_stencil();

	void						set(float width, float height, D3D11_COMPARISON_FUNC comp_func = D3D11_COMPARISON_LESS, D3D11_DEPTH_WRITE_MASK depth_write_mask = D3D11_DEPTH_WRITE_MASK_ALL);

	ID3D11Texture2D				*get_texture() const;
	ID3D11DepthStencilState		*get_ds_state() const;
	ID3D11DepthStencilView		*get_ds_view() const;

	static GRNG_BINDABLE		*create_manager_ptr();

	void						bind() override{ }
};

using GRNG_DEPTH_STENCIL = grng_depth_stencil;
