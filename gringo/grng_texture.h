#pragma once

#include "grng_bindable.h"


class grng_texture : public GRNG_BINDABLE
{
private:
	friend class grng_manager_ptr;

private:
	ID3D11Texture2D					*texture2d = NULL;
	ID3D11ShaderResourceView		*texture_srv = NULL;
	UINT							slot = 0u;


	void		remove_texture2d_memory();
	void		remove_texture_srv_memory();
	void		remove_texture_memory();
	void		set_texture_memory(const LPCWSTR file);

	void		copy_assign(const grng_texture &t);

	static GRNG_BINDABLE		*create_manager_ptr();

public:
	grng_texture	&operator=(const grng_texture &t);
	grng_texture(const grng_texture &t);
	grng_texture();
	grng_texture(const LPCWSTR file, UINT slot = 0u);
	~grng_texture();

	void		set(const LPCWSTR file);
	void		set_slot(UINT slot);

	void		bind() const override
	{
		this->device_context->PSSetShaderResources(this->slot, 1u, &this->texture_srv);
	}
};

using GRNG_TEXTURE = grng_texture;
