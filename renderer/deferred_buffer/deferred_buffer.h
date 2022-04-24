#pragma once

#include "unclassified.h"
#include "def_shaders.h"
#include "texture2d.h"
#include "render_texture.h"
#include "depth_stencil.h"
#include "viewport.h"
#include "sampler.h"
#include "shaders.h"
#include "gfx.h"

#include <vector>


namespace PULSAR
{
	enum G_BUFFER_TYPE
	{
		G_BUFFER_POS,
		G_BUFFER_ALBEDO,
		G_BUFFER_NORMAL,
		G_BUFFER_RMAE,		//	roughness, metalness, ambient, exposure
		G_BUFFER_COUNT,
	};


	class DEFERRED_BUFFER : public PULSAR::unclassified
	{
	private:
		PULSAR::TEXTURE2D			rt_texture[G_BUFFER_COUNT];
		PULSAR::RENDER_TEXTURE		rt[G_BUFFER_COUNT];
		PULSAR::DS_VIEW				ds_view;
		PULSAR::DS_STATE			ds_state;
		PULSAR::VIEWPORT			viewport;

		PULSAR::TEXTURE2D			rt_hdr_texture;
		PULSAR::RENDER_TEXTURE		rt_hdr;

		std::vector<ID3D11RenderTargetView*>	rtv_data;

		PULSAR::SAMPLER			sampler;

		PULSAR::VERT_SHADER		deferred_vs;
		PULSAR::FRAG_SHADER		deferred_fs;

		PULSAR::VERT_SHADER		post_effects_vs;
		PULSAR::FRAG_SHADER		post_effects_fs;

	public:
		DEFERRED_BUFFER		&operator=(const DEFERRED_BUFFER &db)
		{
			int i = -1;
			while (++i < G_BUFFER_COUNT)
			{
				this->rt_texture[i] = db.rt_texture[i];
				this->rt[i] = db.rt[i];
			}
			this->rt_hdr = db.rt_hdr;

			this->ds_view = db.ds_view;
			this->ds_state = db.ds_state;

			return (*this);
		}

		DEFERRED_BUFFER()
		{
			this->deferred_vs = FULLSCREEN_VS;;
			this->deferred_fs.set(L"shaders/deferred/deferred_fs.hlsl", PULSAR::FRAG_SHADER_ENTRY, NULL);

			this->post_effects_vs = FULLSCREEN_VS;
			this->post_effects_fs.set(L"shaders/post_effects/post_effects_fs.hlsl", PULSAR::FRAG_SHADER_ENTRY, NULL);
		}

		void		set_deferred_buffer(float width, float height)
		{
			int i = -1;
			while (++i < G_BUFFER_COUNT)
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
			this->viewport.set(width, height);
		}


		void		bind_rtv()
		{
			int i = -1;
			while (++i < G_BUFFER_COUNT)
				this->rt[i].clear();
			this->ds_view.clear();

			this->device_context->OMSetRenderTargets(G_BUFFER_COUNT, this->rtv_data.data(), this->ds_view.get_view());
			this->ds_state.bind(PULSAR::BIND_SCOPE::GLOBAL);
			this->viewport.bind(PULSAR::BIND_SCOPE::GLOBAL);
		}

		void		bind_srv()
		{
			this->get_hdr_buffer().set_mode(PULSAR::BIND_MODE::RTV);
			this->get_hdr_buffer().bind(PULSAR::BIND_SCOPE::GLOBAL);

			this->deferred_vs.bind(PULSAR::BIND_SCOPE::GLOBAL);
			this->deferred_fs.bind(PULSAR::BIND_SCOPE::GLOBAL);
			GFX::get_curr_camera()->bind_deferred(PULSAR::BIND_SCOPE::GLOBAL);

			int i = -1;
			while (++i < G_BUFFER_COUNT)
				this->rt[i].bind(PULSAR::BIND_SCOPE::GLOBAL);
			this->sampler.bind(PULSAR::BIND_SCOPE::GLOBAL);
			this->viewport.bind(PULSAR::BIND_SCOPE::GLOBAL);
		}

		void		bind_post_effects()
		{
			GFX::get_curr_camera()->bind_post_effects(PULSAR::BIND_SCOPE::GLOBAL);

			this->rt_hdr.set_mode(PULSAR::BIND_MODE::SRV);
			this->rt_hdr.set_ds_view(NULL);
			this->rt_hdr.bind(PULSAR::BIND_SCOPE::GLOBAL);

			this->post_effects_vs.bind(PULSAR::BIND_SCOPE::GLOBAL);
			this->post_effects_fs.bind(PULSAR::BIND_SCOPE::GLOBAL);
			this->sampler.bind(PULSAR::BIND_SCOPE::GLOBAL);
			this->viewport.bind(PULSAR::BIND_SCOPE::GLOBAL);
		}


		PULSAR::TEXTURE2D			&get_render_texture_texture(UINT type);
		PULSAR::RENDER_TEXTURE		&get_render_texture(UINT type);
		PULSAR::RENDER_TEXTURE		&get_hdr_buffer();
		PULSAR::DS_VIEW				&get_ds_view();
		PULSAR::DS_STATE			 &get_ds_state();
		PULSAR::VIEWPORT			 &get_viewport();
	};
}
