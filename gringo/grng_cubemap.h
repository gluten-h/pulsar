#pragma once

#include "grng_bindable.h"


class grng_cubemap : GRNG_BINDABLE
{
private:
	ID3D11ShaderResourceView		*cubemap_srv = NULL;
	UINT							slot = 0u;


	void		remove_cubemap_memory()
	{
		if (this->cubemap_srv)
		{
			this->cubemap_srv->Release();
			this->cubemap_srv = NULL;
		}
	}

	void		create_dds_cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path)
	{
		std::unique_ptr<ScratchImage> scratch_img[6];
		Image img[6];

		uint8_t *pix_data = NULL;

		for (size_t i = 0; i < 6; i++)
		{
			scratch_img[i] = std::make_unique<ScratchImage>();
			HRESULT hr = LoadFromWICFile(wic_path[i], WIC_FLAGS_NONE, NULL, *scratch_img[i]);
			img[i] = *scratch_img[i]->GetImage(0, 0, 0);
		}

		TexMetadata meta_data;
		meta_data.width = img[0].width;
		meta_data.height = img[0].height;
		meta_data.depth = 1;
		meta_data.arraySize = 6;
		meta_data.mipLevels = 1;
		meta_data.miscFlags = TEX_MISC_TEXTURECUBE;
		meta_data.miscFlags2 = TEX_ALPHA_MODE_OPAQUE;
		meta_data.format = img[0].format;
		meta_data.dimension = TEX_DIMENSION_TEXTURE2D;
		
		HRESULT hr = SaveToDDSFile(img, 6u, meta_data, DDS_FLAGS_NONE, output_dds_path);
	}

	void		set_cubemap_memory(LPCWSTR dds_path)
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

public:
	grng_cubemap() : GRNG_BINDABLE()
	{
		this->type = GRNG_BINDABLE_TYPE::CUBEMAP;
	}
	grng_cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path, UINT slot = 0u) : GRNG_BINDABLE()
	{
		this->type = GRNG_BINDABLE_TYPE::CUBEMAP;

		this->create_dds_cubemap(wic_path, output_dds_path);
		this->set_cubemap_memory(output_dds_path);
		this->set_slot(slot);
	}
	grng_cubemap(LPCWSTR dds_path, UINT slot = 0u) : GRNG_BINDABLE()
	{
		this->type = GRNG_BINDABLE_TYPE::CUBEMAP;

		this->set_cubemap_memory(dds_path);
		this->set_slot(slot);
	}

	void		set_cubemap(LPCWSTR *wic_path, LPCWSTR output_dds_path)
	{
		this->create_dds_cubemap(wic_path, output_dds_path);
		this->set_cubemap_memory(output_dds_path);
	}
	void		set_cubemap(LPCWSTR dds_path)
	{
		this->set_cubemap_memory(dds_path);
	}

	void		set_slot(UINT slot)
	{
		this->slot = slot;
	}


	static GRNG_BINDABLE		*create_manager_ptr()
	{
		grng_cubemap *cubemap = new grng_cubemap;
		
		return (cubemap);
	}


	void		bind() override
	{
		this->device_context->PSSetShaderResources(this->slot, 1u, &this->cubemap_srv);
	}

	void		destroy() override
	{
		this->remove_cubemap_memory();
	}
};

using GRNG_CUBEMAP = grng_cubemap;
