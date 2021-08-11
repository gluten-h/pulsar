#pragma once

#include "grng_bindable.h"
#include "grng_bindable_entity.h"


class grng_viewport : public GRNG_BINDABLE
{
private:
	D3D11_VIEWPORT		viewport = { 0 };


	void				set_viewport_memory(float width, float height, float min_depth, float max_depth);
	void				copy_assign(const grng_viewport &v);

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
	grng_viewport		&operator=(const grng_viewport &v);
	grng_viewport(const grng_viewport &v);
	grng_viewport();
	grng_viewport(float width, float height, float min_depth = 0.0f, float max_depth = 1.0f);

	void				set(float width, float height, float min_depth = 0.0f, float max_depth = 1.0f);
	D3D11_VIEWPORT		&get();

	static grng_viewport	*create();

	void		bind() const override
	{
		this->device_context->RSSetViewports(1u, &this->viewport);
		GRNG_BINDABLE::add_unbind(*this);
	}

	void		unbind() const override
	{
		this->device_context->RSSetViewports(0u, NULL);
	}
};

using GRNG_VIEWPORT = grng_viewport;
