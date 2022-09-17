
#include "deferred_render_graph.h"
#include "render_graph/rg_const.h"
#include "exceptions/rg_exception.h"
#include "gfx_resources/framebuffer.h"
#include "gfx_resources/depth_stencil_view.h"
#include "gfx_resources/viewport.h"
#include "gfx_resources/render_texture.h"
#include "renderer/renderer.h"

#include "passes/clear_buffers_pass.h"
#include "passes/shadow_mapping_pass.h"
#include "passes/g_buffer_pass.h"
#include "passes/deferred_pass.h"
#include "passes/skybox_pass.h"
#include "passes/post_effects_pass.h"
#include "passes/present_pass.h"


pulsar::deferred_render_graph::deferred_render_graph(pulsar::framebuffer &framebuffer)
{
	{
		XMUINT2 framebuffer_size = framebuffer.size();

		this->mp_framebuffer = &framebuffer;
		this->mp_dsv = new pulsar::depth_stencil_view(framebuffer_size.x, framebuffer_size.y);
		this->mp_hdr_buffer = new pulsar::render_texture(framebuffer_size.x, framebuffer_size.y, DXGI_FORMAT_R16G16B16A16_FLOAT);

		framebuffer.link(this->mp_dsv);
		framebuffer.link(this->mp_hdr_buffer);

		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
		{
			this->mp_g_buffers[i] = new pulsar::render_texture(framebuffer_size.x, framebuffer_size.y, DXGI_FORMAT_R16G16B16A16_FLOAT, i);
			framebuffer.link(this->mp_g_buffers[i]);
		}

		this->mp_viewport_rq = &pulsar::renderer::instance().viewport_rq();
		this->mp_shadows_rq = &pulsar::renderer::instance().shadows_rq();
	}

	{
		this->mp_framebuffer_source = new pulsar::rg::sync_source<pulsar::framebuffer>(pulsar::RG_G_FRAMEBUFFER, this->mp_framebuffer);
		this->mp_ds_view_source = new pulsar::rg::sync_source<pulsar::depth_stencil_view>(pulsar::RG_G_DSV, this->mp_dsv);
		this->mp_hdr_buffer_source = new pulsar::rg::sync_source<pulsar::render_texture>(pulsar::RG_G_HDR_BUFFER, this->mp_hdr_buffer);

		this->mp_viewport_rq_source = new pulsar::rg::async_source<pulsar::viewport_rq>(pulsar::RG_G_VIEWPORT_RQ, this->mp_viewport_rq);
		this->mp_shadows_rq_source = new pulsar::rg::async_source<pulsar::shadows_rq>(pulsar::RG_G_SHADOWS_RQ, this->mp_shadows_rq);

		this->register_global_source(this->mp_framebuffer_source);
		this->register_global_source(this->mp_ds_view_source);
		this->register_global_source(this->mp_hdr_buffer_source);

		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
		{
			this->mp_g_buffers_sources[i] = new pulsar::rg::sync_source<pulsar::render_texture>(pulsar::RG_G_G_BUFFERS[i], this->mp_g_buffers[i]);
			this->register_global_source(this->mp_g_buffers_sources[i]);
		}

		this->register_global_source(this->mp_viewport_rq_source);
		this->register_global_source(this->mp_shadows_rq_source);
	}

	{
		this->mp_clear_buffers_pass = new pulsar::clear_buffers_pass(pulsar::RG_CLEAR_BUFFERS_PASS_NAME);

		this->mp_clear_buffers_pass->link_input(pulsar::RG_G_FRAMEBUFFER, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_FRAMEBUFFER);
		this->mp_clear_buffers_pass->link_input(pulsar::RG_G_DSV, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_DSV);
		this->mp_clear_buffers_pass->link_input(pulsar::RG_G_HDR_BUFFER, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_HDR_BUFFER);

		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
			this->mp_clear_buffers_pass->link_input(pulsar::RG_G_G_BUFFERS[i], pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_G_BUFFERS[i]);

		this->add_pass(pulsar::RG_CLEAR_BUFFERS_PASS_LEVEL, this->mp_clear_buffers_pass);
	}
	{
		this->mp_shadow_mapping_pass = new pulsar::shadow_mapping_pass(pulsar::RG_SHADOW_MAPPING_PASS_NAME);

		this->mp_shadow_mapping_pass->link_input(pulsar::RG_G_SHADOWS_RQ, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_SHADOWS_RQ);

		this->add_pass(pulsar::RG_SHADOW_MAPPING_PASS_LEVEL, this->mp_shadow_mapping_pass);
	}
	{
		this->mp_g_buffer_pass = new pulsar::g_buffer_pass(pulsar::RG_G_BUFFER_PASS_NAME);

		this->mp_g_buffer_pass->link_input(pulsar::RG_G_DSV, this->mp_clear_buffers_pass->name() + std::string(".") + pulsar::RG_G_DSV);
		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
			this->mp_g_buffer_pass->link_input(pulsar::RG_G_G_BUFFERS[i], this->mp_clear_buffers_pass->name() + std::string(".") + pulsar::RG_G_G_BUFFERS[i]);

		this->mp_g_buffer_pass->link_input(pulsar::RG_G_VIEWPORT_RQ, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_VIEWPORT_RQ);

		this->add_pass(pulsar::RG_G_BUFFER_PASS_LEVEL, this->mp_g_buffer_pass);
	}
	{
		this->mp_deferred_pass = new pulsar::deferred_pass(pulsar::RG_DEFERRED_PASS_NAME);
	
		this->mp_deferred_pass->link_input(pulsar::RG_G_DSV, this->mp_g_buffer_pass->name() + std::string(".") + pulsar::RG_G_DSV);
		this->mp_deferred_pass->link_input(pulsar::RG_G_HDR_BUFFER, this->mp_clear_buffers_pass->name() + std::string(".") + pulsar::RG_G_HDR_BUFFER);
		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
			this->mp_deferred_pass->link_input(pulsar::RG_G_G_BUFFERS[i], this->mp_g_buffer_pass->name() + std::string(".") + pulsar::RG_G_G_BUFFERS[i]);
	
		this->add_pass(pulsar::RG_DEFERRED_PASS_LEVEL, this->mp_deferred_pass);
	}
	{
		this->mp_skybox_pass = new pulsar::skybox_pass(pulsar::RG_SKYBOX_PASS_NAME);
	
		this->mp_skybox_pass->link_input(pulsar::RG_G_DSV, this->mp_deferred_pass->name() + std::string(".") + pulsar::RG_G_DSV);
		this->mp_skybox_pass->link_input(pulsar::RG_G_HDR_BUFFER, this->mp_deferred_pass->name() + std::string(".") + pulsar::RG_G_HDR_BUFFER);
	
		this->add_pass(pulsar::RG_SKYBOX_PASS_LEVEL, this->mp_skybox_pass);
	}
	{
		this->mp_post_effects_pass = new pulsar::post_effects_pass(pulsar::RG_POST_EFFECTS_PASS_NAME);
	
		this->mp_post_effects_pass->link_input(pulsar::RG_G_FRAMEBUFFER, this->mp_clear_buffers_pass->name() + std::string(".") + pulsar::RG_G_FRAMEBUFFER);
		this->mp_post_effects_pass->link_input(pulsar::RG_G_HDR_BUFFER, this->mp_skybox_pass->name() + std::string(".") + pulsar::RG_G_HDR_BUFFER);
	
		this->add_pass(pulsar::RG_POST_EFFECTS_PASS_LEVEL, this->mp_post_effects_pass);
	}
	{
		this->mp_present_pass = new pulsar::present_pass(pulsar::RG_PRESENT_PASS_NAME);
		this->mp_present_pass->link_input(pulsar::RG_G_FRAMEBUFFER, this->mp_post_effects_pass->name() + "." + pulsar::RG_G_FRAMEBUFFER);
		this->add_pass(pulsar::RG_PRESENT_PASS_LEVEL, this->mp_present_pass);
	}

	this->compile();
	this->validate();
}

pulsar::deferred_render_graph::~deferred_render_graph()
{
	{
		delete this->mp_dsv;
		delete this->mp_hdr_buffer;

		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
			delete this->mp_g_buffers[i];
	}
	{
		delete this->mp_framebuffer_source;
		delete this->mp_ds_view_source;
		delete this->mp_hdr_buffer_source;

		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
			delete this->mp_g_buffers_sources[i];

		delete this->mp_viewport_rq_source;
		delete this->mp_shadows_rq_source;
	}
	{
		delete this->mp_clear_buffers_pass;
		delete this->mp_g_buffer_pass;
		delete this->mp_deferred_pass;
		delete this->mp_skybox_pass;
		delete this->mp_present_pass;
	}
}
