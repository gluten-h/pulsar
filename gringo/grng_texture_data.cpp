
#include "grng_texture.h"


void			grng_texture::set_texture_memory(const LPCWSTR file)
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(this->device, file, NULL, NULL, &this->texture_srv, NULL);
}

void			grng_texture::remove_texture_memory()
{
	if (this->texture_srv)
	{
		ULONG ref_count = this->texture_srv->Release();
		if (ref_count == 0)
			this->texture_srv = NULL;
	}
}


void			grng_texture::set(const LPCWSTR file)
{
	this->remove_texture_memory();
	this->set_texture_memory(file);
}

void			grng_texture::set_slot(UINT slot)
{
	this->slot = slot;
}

GRNG_BINDABLE	*grng_texture::create_manager_ptr()
{
	grng_texture *tex = new grng_texture;

	return (tex);
}
