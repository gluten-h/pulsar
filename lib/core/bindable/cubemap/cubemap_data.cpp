
#include "cubemap.h"


void		PULSAR::CUBEMAP::remove_tex2d_memory()
{
	if (this->tex2d)
	{
		ULONG ref_count = this->tex2d->Release();
		if (ref_count == 0)
			this->tex2d = NULL;
	}
}

void		PULSAR::CUBEMAP::remove_cubemap_srv_memory()
{
	if (this->cubemap_srv)
	{
		ULONG ref_count = this->cubemap_srv->Release();
		if (ref_count == 0)
			this->cubemap_srv = NULL;
	}
}

void		PULSAR::CUBEMAP::remove_cubemap_memory()
{
	this->remove_tex2d_memory();
	this->remove_cubemap_srv_memory();
}

void		PULSAR::CUBEMAP::set_cubemap_memory(LPCWSTR dds_path)
{
	HRESULT hr;

	GFX_ASSERT(CreateDDSTextureFromFileEx(this->device, PULSAR::filesystem::file_path(dds_path).c_str(), 6u, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0u,
												D3D11_RESOURCE_MISC_TEXTURECUBE, false, (ID3D11Resource**)&this->tex2d, &this->cubemap_srv));
}

void		PULSAR::CUBEMAP::set(LPCWSTR *wic_path, LPCWSTR output_dds_path, PULSAR::CUBEMAP_DDS dds_behavior)
{
	this->remove_cubemap_memory();
	switch (dds_behavior)
	{
		case PULSAR::CUBEMAP_DDS::OVERWRITE:
		{
			this->create_dds_cubemap(wic_path, output_dds_path);
			break;
		}
		case PULSAR::CUBEMAP_DDS::KEEP_IF_EXISTS:
		{
			if (std::filesystem::exists(output_dds_path))
				break;
			this->create_dds_cubemap(wic_path, output_dds_path);
			break;
		}
	}
	this->set_cubemap_memory(output_dds_path);
}

void		PULSAR::CUBEMAP::set(LPCWSTR dds_path)
{
	this->remove_cubemap_memory();
	this->set_cubemap_memory(dds_path);
}

void		PULSAR::CUBEMAP::set_slot(UINT slot)
{
	this->slot = slot;
}


PULSAR::CUBEMAP		*PULSAR::CUBEMAP::create()
{
	return ((PULSAR::CUBEMAP*)PULSAR::BINDABLE::add_to_manager(new PULSAR::CUBEMAP));
}
