#pragma once

#include "grng_bindable.h"
#include "grng_bindable_entity.h"


class grng_depth_stencil_view : public GRNG_BINDABLE, public GRNG_BUFFER_RESOURCE
{
private:
	ID3D11Texture2D				*ds_texture = NULL;
	ID3D11DepthStencilView		*ds_view = NULL;


	void						set_ds_memory(float width, float height);

	void						remove_ds_texture_memory();
	void						remove_ds_view_memory();
	void						remove_ds_memory();

	void						copy_assign(const grng_depth_stencil_view &dsv);

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
	grng_depth_stencil_view			&operator=(const grng_depth_stencil_view &dsv);
	grng_depth_stencil_view(const grng_depth_stencil_view &dsv);
	grng_depth_stencil_view();
	grng_depth_stencil_view(float width, float height);
	~grng_depth_stencil_view();

	void						set(float width, float height);

	ID3D11Texture2D				*get_texture();
	ID3D11DepthStencilView		*get_view();

	static grng_depth_stencil_view		*create();

	void		clear() override
	{
		this->device_context->ClearDepthStencilView(this->ds_view, D3D11_CLEAR_DEPTH, 1.0f, 0u);
	}

	void		bind() const override{ }
	void		unbind() const override{ }
};

using GRNG_DEPTH_STENCIL_VIEW = grng_depth_stencil_view;
using GRNG_DS_VIEW = grng_depth_stencil_view;
