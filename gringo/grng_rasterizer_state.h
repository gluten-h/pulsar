#pragma once

#include "grng_bindable.h"
#include "grng_bindable_entity.h"


class grng_rasterizer_state : public GRNG_BINDABLE
{
private:
	ID3D11RasterizerState		*rs = NULL;


	void		remove_rs_memory();
	void		set_rs_memory(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);

	void		copy_assign(const grng_rasterizer_state &rs);

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
	grng_rasterizer_state		&operator=(const grng_rasterizer_state &rs);
	grng_rasterizer_state(const grng_rasterizer_state &rs);
	grng_rasterizer_state();
	grng_rasterizer_state(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);
	~grng_rasterizer_state();

	void					set(D3D11_FILL_MODE fill_mode, D3D11_CULL_MODE cull_mode);
	ID3D11RasterizerState	*get();

	static grng_rasterizer_state	*create();

	void		bind() const override
	{
		this->device_context->RSSetState(this->rs);
		GRNG_BINDABLE::add_unbind(*this);
	}

	void		unbind() const override
	{
		this->device_context->RSSetState(NULL);
	}
};

using GRNG_RASTERIZER_STATE = grng_rasterizer_state;
