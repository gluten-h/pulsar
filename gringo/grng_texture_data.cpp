
#include "grng_texture.h"


void		grng_texture::remove_texture2d_memory()
{
	if (this->texture2d)
	{
		ULONG ref_count = this->texture2d->Release();
		if (ref_count == 0)
			this->texture2d = NULL;
	}
}

void		grng_texture::remove_texture_srv_memory()
{
	if (this->texture_srv)
	{
		ULONG ref_count = this->texture_srv->Release();
		if (ref_count == 0)
			this->texture_srv = NULL;
	}
}

void			grng_texture::remove_texture_memory()
{
	this->remove_texture2d_memory();
	this->remove_texture_srv_memory();
}

void			grng_texture::set_texture_memory(const LPCWSTR file)
{
	HRESULT hr;

	GRNG_GFX_ASSERT(CreateWICTextureFromFile(this->device, file, (ID3D11Resource**)&this->texture2d, &this->texture_srv));
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


grng_texture	*grng_texture::create()
{
	grng_texture *tex = new grng_texture;
	tex->id = GRNG_BM.add(tex);
	if (tex->id == -1)
	{
		delete tex;
		return (NULL);
	}
	tex->is_alloc = true;

	return (tex);
}
