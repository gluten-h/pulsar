
#include "grng_cubemap.h"


void		grng_cubemap::remove_tex2d_memory()
{
	if (this->tex2d)
	{
		ULONG ref_count = this->tex2d->Release();
		if (ref_count == 0)
			this->tex2d = NULL;
	}
}

void		grng_cubemap::remove_cubemap_srv_memory()
{
	if (this->cubemap_srv)
	{
		ULONG ref_count = this->cubemap_srv->Release();
		if (ref_count == 0)
			this->cubemap_srv = NULL;
	}
}

void		grng_cubemap::remove_cubemap_memory()
{
	this->remove_tex2d_memory();
	this->remove_cubemap_srv_memory();
}

void		grng_cubemap::set_cubemap_memory(LPCWSTR dds_path)
{
	HRESULT hr = CreateDDSTextureFromFileEx(this->device, dds_path, 6u, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0u,
											D3D11_RESOURCE_MISC_TEXTURECUBE, false, (ID3D11Resource**)&this->tex2d, &this->cubemap_srv);
}

void		grng_cubemap::set(LPCWSTR *wic_path, LPCWSTR output_dds_path, GRNG_CUBEMAP_DDS dds_behavior)
{
	this->remove_cubemap_memory();
	switch (dds_behavior)
	{
		case GRNG_CUBEMAP_DDS::OVERWRITE:
		{
			this->create_dds_cubemap(wic_path, output_dds_path);
			break;
		}
		case GRNG_CUBEMAP_DDS::KEEP_IF_EXISTS:
		{
			std::wstring out_path(output_dds_path);
			if (std::filesystem::exists(out_path))
				break;
			this->create_dds_cubemap(wic_path, output_dds_path);
			break;
		}
	}
	this->set_cubemap_memory(output_dds_path);
}

void		grng_cubemap::set(LPCWSTR dds_path)
{
	this->remove_cubemap_memory();
	this->set_cubemap_memory(dds_path);
}

void		grng_cubemap::set_slot(UINT slot)
{
	this->slot = slot;
}

GRNG_BINDABLE		*grng_cubemap::create_manager_ptr()
{
	grng_cubemap *cubemap = new grng_cubemap;

	return (cubemap);
}
