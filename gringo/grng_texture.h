#pragma once

#include "grng_bindable.h"


class grng_texture : public GRNG_BINDABLE
{
private:
	ID3D11ShaderResourceView		*texture_srv = NULL;
	UINT							slot = 0u;


	void		set_texture_memory(const LPCWSTR file);
	void		remove_texture_memory();

	void		copy_assign(const grng_texture &t);

public:
	grng_texture	&operator=(const grng_texture &t);
	grng_texture(const grng_texture &t);
	grng_texture();
	grng_texture(const LPCWSTR file, UINT slot = 0u);
	~grng_texture();

	void		set(const LPCWSTR file);
	void		set_slot(UINT slot);

	static GRNG_BINDABLE		*create_manager_ptr();

	void		bind() override
	{
		this->device_context->PSSetShaderResources(this->slot, 1u, &this->texture_srv);
	}
};

using GRNG_TEXTURE = grng_texture;
