
#include "texture.h"


void		PULSAR::TEXTURE::remove_texture2d_memory()
{
	if (this->texture2d)
	{
		ULONG ref_count = this->texture2d->Release();
		if (ref_count == 0)
			this->texture2d = NULL;
	}
}

void		PULSAR::TEXTURE::remove_texture_srv_memory()
{
	if (this->texture_srv)
	{
		ULONG ref_count = this->texture_srv->Release();
		if (ref_count == 0)
			this->texture_srv = NULL;
	}
}

void		PULSAR::TEXTURE::remove_texture_memory()
{
	this->remove_texture2d_memory();
	this->remove_texture_srv_memory();
}

void		PULSAR::TEXTURE::set_texture_memory(const LPCWSTR file)
{
	HRESULT hr;

	GFX_ASSERT(CreateWICTextureFromFile(this->device, PULSAR::filesystem::file_path(file).c_str(), (ID3D11Resource**)&this->texture2d, &this->texture_srv));
}

void		PULSAR::TEXTURE::set(const LPCWSTR file)
{
	this->remove_texture_memory();
	this->set_texture_memory(file);
}

void		PULSAR::TEXTURE::set_slot(UINT slot)
{
	this->slot = slot;
}


PULSAR::TEXTURE		*PULSAR::TEXTURE::create()
{
	return ((PULSAR::TEXTURE*)PULSAR::BINDABLE::add_to_manager(new PULSAR::TEXTURE));
}
