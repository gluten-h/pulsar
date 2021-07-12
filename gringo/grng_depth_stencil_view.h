#pragma once

#include "grng_bindable.h"


class grng_depth_stencil_view : public GRNG_BINDABLE
{
private:
	ID3D11Texture2D				*ds_texture = NULL;
	ID3D11DepthStencilView		*ds_view = NULL;


	void						set_ds_memory(float width, float height);

	void						remove_ds_texture_memory();
	void						remove_ds_view_memory();
	void						remove_ds_memory();

	void						copy_assign(const grng_depth_stencil_view &dsv);

public:
	grng_depth_stencil_view			&operator=(const grng_depth_stencil_view &dsv);
	grng_depth_stencil_view(const grng_depth_stencil_view &dsv);
	grng_depth_stencil_view();
	grng_depth_stencil_view(float width, float height);
	~grng_depth_stencil_view();

	void						set(float width, float height);

	ID3D11Texture2D				*get_texture();
	ID3D11DepthStencilView		*get_view();

	static GRNG_BINDABLE		*create_manager_ptr();

	void						bind() const override{ }
};

using GRNG_DEPTH_STENCIL_VIEW = grng_depth_stencil_view;
using GRNG_DS_VIEW = grng_depth_stencil_view;
