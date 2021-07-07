#pragma once

#include "grng_bindable.h"


class grng_depth_stencil : public GRNG_BINDABLE
{
private:
	ID3D11Texture2D					*ds_texture = NULL;
	ID3D11DepthStencilState			*ds_state = NULL;
	ID3D11DepthStencilView			*ds_view = NULL;


	void		set_ds_memory(float width, float height)
	{
		HRESULT hr;

		D3D11_TEXTURE2D_DESC td;
		D3D11_DEPTH_STENCIL_DESC dsd;
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));
		ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

		td.Width = width;
		td.Height = height;
		td.MipLevels = 1u;
		td.ArraySize = 1u;
		td.Format = DXGI_FORMAT_D32_FLOAT;
		td.SampleDesc.Count = 1u;
		td.SampleDesc.Quality = 0u;
		td.Usage = D3D11_USAGE_DEFAULT;
		td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		td.CPUAccessFlags = 0u;
		td.MiscFlags = 0u;
		hr = this->device->CreateTexture2D(&td, NULL, &this->ds_texture);

		dsd.DepthEnable = TRUE;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.DepthFunc = D3D11_COMPARISON_LESS;
		hr = this->device->CreateDepthStencilState(&dsd, &this->ds_state);

		dsvd.Format = DXGI_FORMAT_D32_FLOAT;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		hr = this->device->CreateDepthStencilView(this->ds_texture, &dsvd, &this->ds_view);
	}

	void		remove_ds_memory()
	{
		if (this->ds_texture)
		{
			this->ds_texture->Release();
			this->ds_texture = NULL;
		}
		if (this->ds_state)
		{
			this->ds_state->Release();
			this->ds_state = NULL;
		}
		if (this->ds_view)
		{
			this->ds_view->Release();
			this->ds_view = NULL;
		}
	}

public:
	grng_depth_stencil		&operator=(const grng_depth_stencil &ds)
	{
		this->ds_texture = ds.ds_texture;
		this->ds_state = ds.ds_state;
		this->ds_view = ds.ds_view;

		return (*this);
	}

	grng_depth_stencil() : GRNG_BINDABLE()
	{
		this->type = GRNG_BINDABLE_TYPE::DEPTH_STENCIL;
	}
	grng_depth_stencil(float width, float height) : GRNG_BINDABLE()
	{
		this->type = GRNG_BINDABLE_TYPE::DEPTH_STENCIL;

		this->set_ds_memory(width, height);
	}

	~grng_depth_stencil()
	{
		this->remove_ds_memory();
	}

	void			set(float width, float height)
	{
		this->remove_ds_memory();
		this->set_ds_memory(width, height);
	}


	ID3D11Texture2D				*get_texture() const
	{
		return (this->ds_texture);
	}

	ID3D11DepthStencilState		*get_ds_state() const
	{
		return (this->ds_state);
	}

	ID3D11DepthStencilView		*get_ds_view() const
	{
		return (this->ds_view);
	}


	static GRNG_BINDABLE		*create_manager_ptr()
	{
		grng_depth_stencil *ds = new grng_depth_stencil;

		return (ds);
	}


	void		bind() override{ }

	void		destroy() override
	{
		this->remove_ds_memory();
	}
};

using GRNG_DEPTH_STENCIL = grng_depth_stencil;
