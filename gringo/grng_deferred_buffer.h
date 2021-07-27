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
	GRNG_G_BUFFER_RMAE,
	GRNG_G_BUFFER_COUNT,
};


class grng_deferred_buffer : public GRNG_ID3D
{
private:
	GRNG_TEXTURE2D			rt_texture[GRNG_G_BUFFER_COUNT];
	GRNG_RENDER_TEXTURE		rt[GRNG_G_BUFFER_COUNT];
	GRNG_DS_VIEW			ds_view;
	GRNG_DS_STATE			ds_state;
	D3D11_VIEWPORT			viewport = { 0 };

	GRNG_TEXTURE2D			rt_hdr_texture;
	GRNG_RENDER_TEXTURE		rt_hdr;

	std::vector<ID3D11RenderTargetView*>	rtv_data;

	GRNG_SAMPLER			sampler;

	GRNG_VERT_SHADER		deferred_vs;			//		MAYBE MAKE THESE STATIC
	GRNG_FRAG_SHADER		deferred_fs;

	GRNG_VERT_SHADER		post_effects_vs;		//		MAYBE MAKE THESE STATIC
	GRNG_FRAG_SHADER		post_effects_fs;

public:
	grng_deferred_buffer	&operator=(const grng_deferred_buffer &db)
	{
		int i = -1;
		while (++i < GRNG_G_BUFFER_COUNT)
		{
			this->rt_texture[i] = db.rt_texture[i];
			this->rt[i] = db.rt[i];
		}
		this->rt_hdr = db.rt_hdr;

		this->ds_view = db.ds_view;
		this->ds_state = db.ds_state;

		return (*this);
	}

	grng_deferred_buffer() : GRNG_ID3D()
	{
		this->deferred_vs.set(L"deferred_vs.hlsl", GRNG_VERT_ENTRY, NULL);
		this->deferred_fs.set(L"deferred_fs.hlsl", GRNG_FRAG_ENTRY, NULL);

		this->post_effects_vs.set(L"post_effects_vs.hlsl", GRNG_VERT_ENTRY, NULL);
		this->post_effects_fs.set(L"post_effects_fs.hlsl", GRNG_FRAG_ENTRY, NULL);
	}

	void		set_deferred_buffer(float width, float height)
	{
		int i = -1;
		while (++i < GRNG_G_BUFFER_COUNT)
		{
			this->rt_texture[i].set_texture(width, height, DXGI_FORMAT_R16G16B16A16_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, 0u);
			this->rt[i].set(this->rt_texture[i].get_texture());
			this->rt[i].set_slot(i);

			this->rtv_data.push_back(this->rt[i].get_render_target());
		}
		this->rt_hdr_texture.set_texture(width, height, DXGI_FORMAT_R16G16B16A16_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, 0u);
		this->rt_hdr.set(this->rt_hdr_texture.get_texture());

		this->ds_view.set(width, height);
		this->ds_state.set(TRUE, D3D11_COMPARISON_LESS, D3D11_DEPTH_WRITE_MASK_ALL);

		this->viewport.TopLeftX = 0.0f;
		this->viewport.TopLeftY = 0.0f;
		this->viewport.Width = width;
		this->viewport.Height = height;
		this->viewport.MinDepth = 0.0f;
		this->viewport.MaxDepth = 1.0f;
	}


	void		bind_rtv()
	{
		int i = -1;
		while (++i < GRNG_G_BUFFER_COUNT)
			this->rt[i].clear();
		this->ds_view.clear();

		this->device_context->OMSetRenderTargets(GRNG_G_BUFFER_COUNT, this->rtv_data.data(), this->ds_view.get_view());
		this->ds_state.bind();
		this->device_context->RSSetViewports(1, &this->viewport);
	}

	void		bind_srv()
	{
		this->deferred_vs.bind();
		this->deferred_fs.bind();
		GRNG_GFX::get_curr_camera()->bind_deferred();

		int i = -1;
		while (++i < GRNG_G_BUFFER_COUNT)
			this->rt[i].bind();
		this->sampler.bind();
	}

	void		bind_post_effects()
	{
		GRNG_GFX::get_curr_camera()->bind_post_effects();
		this->rt_hdr.bind();
		this->post_effects_vs.bind();
		this->post_effects_fs.bind();
		this->sampler.bind();
	}


	GRNG_TEXTURE2D				&get_render_texture_texture(UINT type);
	GRNG_RENDER_TEXTURE			&get_render_texture(UINT type);
	GRNG_RENDER_TEXTURE			&get_hdr_buffer();
	GRNG_DS_VIEW				&get_ds_view();
	GRNG_DS_STATE				&get_ds_state();
	D3D11_VIEWPORT				&get_viewport();
};

using GRNG_DEFERRED_BUFFER = grng_deferred_buffer;
