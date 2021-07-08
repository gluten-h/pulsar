
#include "grng_cubemap.h"


void		grng_cubemap::remove_cubemap_memory()
{
	if (this->cubemap_srv)
	{
		ULONG ref_count = this->cubemap_srv->Release();
		if (ref_count == 0)
			this->cubemap_srv = NULL;
	}
}

void		grng_cubemap::set_cubemap_memory(LPCWSTR dds_path)
{
	D3DX11_IMAGE_LOAD_INFO info;
	info.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	ID3D11Texture2D *tex = NULL;
	HRESULT hr = D3DX11CreateTextureFromFile(this->device, dds_path, &info, NULL, (ID3D11Resource**)&tex, NULL);

	D3D11_TEXTURE2D_DESC td;
	tex->GetDesc(&td);

	D3D11_SHADER_RESOURCE_VIEW_DESC vd;
	vd.Format = td.Format;
	vd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	vd.TextureCube.MipLevels = 1u;
	vd.TextureCube.MostDetailedMip = 0u;

	hr = this->device->CreateShaderResourceView(tex, &vd, &this->cubemap_srv);
}

void		grng_cubemap::set(LPCWSTR *wic_path, LPCWSTR output_dds_path)
{
	this->remove_cubemap_memory();
	this->create_dds_cubemap(wic_path, output_dds_path);
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
