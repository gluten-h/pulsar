#pragma once

#include "grng_texture2d.h"
#include "grng_render_texture.h"
#include "grng_depth_stencil.h"
#include "grng_sampler.h"
#include "grng_shaders.h"
#include "grng_gfx.h"

#include <vector>


enum GRNG_G_BUFFER_TYPE
{
	GRNG_G_BUFFER_POS,
	GRNG_G_BUFFER_ALBEDO,
	GRNG_G_BUFFER_NORMAL,
	GRNG_G_BUFFER_RMA,
	GRNG_G_BUFFER_COUNT
};


class grng_deferred_buffer : public GRNG_ID3D
{
private:
	GRNG_TEXTURE2D			rt_texture[GRNG_G_BUFFER_COUNT];
	GRNG_RENDER_TEXTURE		rt[GRNG_G_BUFFER_COUNT];
	GRNG_DEPTH_STENCIL		ds;
	D3D11_VIEWPORT			viewport = { 0 };

	std::vector<ID3D11RenderTargetView*>	rtv_data;

	GRNG_SAMPLER			sampler;

	GRNG_VERT_SHADER		deferred_vs;
	GRNG_FRAG_SHADER		deferred_fs;

public:
	grng_deferred_buffer	&operator=(const grng_deferred_buffer &db)
	{
		int i = -1;
		while (++i < GRNG_G_BUFFER_COUNT)
		{
			this->rt_texture[i] = db.rt_texture[i];
			this->rt[i] = db.rt[i];
		}
		this->ds = db.ds;

		return (*this);
	}

	grng_deferred_buffer() : GRNG_ID3D()
	{
		this->deferred_vs.set(L"deferred_vs.hlsl", GRNG_VERT_ENTRY, NULL);
		this->deferred_fs.set(L"deferred_fs.hlsl", GRNG_FRAG_ENTRY, NULL);
	}

	void		set_deferred_buffer(float width, float height)
	{
		int i = -1;
		while (++i < GRNG_G_BUFFER_COUNT)
		{
			this->rt_texture[i].set_texture(width, height, DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, 0u);
			this->rt[i].set(this->rt_texture[i].get_texture());
			this->rt[i].set_slot(i);

			this->rtv_data.push_back(this->rt[i].get_render_target());
		}
		this->ds.set(width, height);

		this->viewport.TopLeftX = 0.0f;
		this->viewport.TopLeftY = 0.0f;
		this->viewport.Width = width;
		this->viewport.Height = height;
		this->viewport.MinDepth = 0.0f;
		this->viewport.MaxDepth = 1.0f;
	}


	void		bind_as_rtv()
	{
		int i = -1;
		while (++i < GRNG_G_BUFFER_COUNT)
		{
			this->device_context->ClearRenderTargetView(this->rt[i].get_render_target(), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		}
		this->device_context->ClearDepthStencilView(this->ds.get_ds_view(), D3D11_CLEAR_DEPTH, 1.0f, 0u);

		this->device_context->OMSetRenderTargets(GRNG_G_BUFFER_COUNT, this->rtv_data.data(), this->ds.get_ds_view());
		this->device_context->OMSetDepthStencilState(this->ds.get_ds_state(), 1u);
		this->device_context->RSSetViewports(1, &this->viewport);
	}

	void		bind_as_srv()
	{
		this->deferred_vs.bind();
		this->deferred_fs.bind();

		GRNG_GFX::get_curr_camera()->bind();

		int i = -1;
		while (++i < GRNG_G_BUFFER_COUNT)
		{
			this->rt[i].bind();
		}
		this->sampler.bind();
	}


	GRNG_TEXTURE2D				&get_render_texture_texture(UINT type);
	GRNG_RENDER_TEXTURE			&get_render_texture(UINT type);
	GRNG_DEPTH_STENCIL			&get_depth_stencil();
	D3D11_VIEWPORT				&get_viewport();
};

using GRNG_DEFERRED_BUFFER = grng_deferred_buffer;
