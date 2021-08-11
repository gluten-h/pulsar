#pragma once

#include "grng_bindable.h"
#include "grng_bindable_entity.h"


class grng_texture : public GRNG_BINDABLE
{
private:
	ID3D11Texture2D					*texture2d = NULL;
	ID3D11ShaderResourceView		*texture_srv = NULL;
	UINT							slot = 0u;


	void		remove_texture2d_memory();
	void		remove_texture_srv_memory();
	void		remove_texture_memory();
	void		set_texture_memory(const LPCWSTR file);

	void		copy_assign(const grng_texture &t);

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
	grng_texture	&operator=(const grng_texture &t);
	grng_texture(const grng_texture &t);
	grng_texture();
	grng_texture(const LPCWSTR file, UINT slot = 0u);
	~grng_texture();

	void		set(const LPCWSTR file);
	void		set_slot(UINT slot);

	static grng_texture		*create();

	void		bind() const override
	{
		this->device_context->PSSetShaderResources(this->slot, 1u, &this->texture_srv);
		GRNG_BINDABLE::add_unbind(*this);
	}

	void		unbind() const override
	{
		this->device_context->PSGetShaderResources(this->slot, 0u, NULL);
	}
};

using GRNG_TEXTURE = grng_texture;
