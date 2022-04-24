
#include "cubemap.h"
#include "filesystem/filesystem.h"


void	PULSAR::cubemap::free()
{
	if (this->mp_texture2d)
	{
		this->mp_texture2d->Release();
		this->mp_texture2d = NULL;
	}
	if (this->mp_srv)
	{
		this->mp_srv->Release();
		this->mp_srv = NULL;
	}
}

void	PULSAR::cubemap::create_cubemap(LPCWSTR dds_path)
{
	GFX_ASSERT(CreateDDSTextureFromFileEx(PULSAR::gfx::get().device(), PULSAR::filesystem::absolute_path(dds_path).c_str(), 6u, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0u,
												D3D11_RESOURCE_MISC_TEXTURECUBE, false, (ID3D11Resource**)&this->mp_texture2d, &this->mp_srv));
}

void	PULSAR::cubemap::set(LPCWSTR *wic_path, LPCWSTR output_dds_path, PULSAR::CUBEMAP_DDS dds_behavior)
{
	this->free();

	switch (dds_behavior)
	{
		case PULSAR::CUBEMAP_DDS::OVERWRITE:
		{
			this->save_dds_cubemap(wic_path, output_dds_path);
			break;
		}
		case PULSAR::CUBEMAP_DDS::KEEP_IF_EXISTS:
		{
			if (std::filesystem::exists(PULSAR::filesystem::absolute_path(output_dds_path)))
				break;
			this->save_dds_cubemap(wic_path, output_dds_path);
			break;
		}
	}
	this->create_cubemap(output_dds_path);
}

void		PULSAR::cubemap::set(LPCWSTR dds_path)
{
	this->free();
	this->create_cubemap(dds_path);
}

void		PULSAR::cubemap::set_slot(UINT slot)
{
	this->m_slot = slot;
}
