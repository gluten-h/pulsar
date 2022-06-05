
#include "deferred_render_graph.h"
#include "render_graph/rg_const.h"
#include "exceptions/rg_exception.h"
#include "framebuffer/framebuffer.h"
#include "depth_stencil/depth_stencil_view.h"
#include "viewport/viewport.h"
#include "render_texture/render_texture.h"

#include "passes/clear_buffers_pass.h"
#include "passes/g_buffer_pass.h"
#include "passes/deferred_pass.h"
#include "passes/skybox_pass.h"
#include "passes/post_effects_pass.h"
#include "passes/present_pass.h"


pulsar::deferred_render_graph::deferred_render_graph(pulsar::viewport &viewport, pulsar::framebuffer &framebuffer)
{
	{
		XMUINT2 framebuffer_size = framebuffer.size();

		this->mp_viewport = &viewport;
		this->mp_framebuffer = &framebuffer;
		this->mp_ds_view = new pulsar::depth_stencil_view(framebuffer_size.x, framebuffer_size.y);
		this->mp_hdr_buffer = new pulsar::render_texture(framebuffer_size.x, framebuffer_size.y, DXGI_FORMAT_R16G16B16A16_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, 0u);

		viewport.link_buffer_resource(this->mp_ds_view);
		viewport.link_buffer_resource(this->mp_hdr_buffer);

		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
		{
			this->mp_g_buffers[i] = new pulsar::render_texture(framebuffer_size.x, framebuffer_size.y, DXGI_FORMAT_R16G16B16A16_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, 0u);
			this->mp_g_buffers[i]->set_slot(i);
			viewport.link_buffer_resource(this->mp_g_buffers[i]);
		}
	}

	{
		this->mp_framebuffer_source = new pulsar::rg::buffer_source<pulsar::framebuffer>(pulsar::RG_G_FRAMEBUFFER, this->mp_framebuffer);
		this->mp_ds_view_source = new pulsar::rg::buffer_source<pulsar::depth_stencil_view>(pulsar::RG_G_DS_VIEW, this->mp_ds_view);
		this->mp_viewport_source = new pulsar::rg::bindable_source<pulsar::viewport>(pulsar::RG_G_VIEWPORT, this->mp_viewport);
		this->mp_hdr_buffer_source = new pulsar::rg::buffer_source<pulsar::render_texture>(pulsar::RG_G_HDR_BUFFER, this->mp_hdr_buffer);

		this->register_global_source(this->mp_framebuffer_source);
		this->register_global_source(this->mp_ds_view_source);
		this->register_global_source(this->mp_viewport_source);
		this->register_global_source(this->mp_hdr_buffer_source);

		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
		{
			this->mp_g_buffers_sources[i] = new pulsar::rg::buffer_source<pulsar::render_texture>(pulsar::RG_G_G_BUFFERS[i], this->mp_g_buffers[i]);
			this->register_global_source(this->mp_g_buffers_sources[i]);
		}
	}

	{
		this->mp_clear_buffers_pass = new pulsar::clear_buffers_pass("clear_buffers");

		this->mp_clear_buffers_pass->link_input(pulsar::RG_G_FRAMEBUFFER, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_FRAMEBUFFER);
		this->mp_clear_buffers_pass->link_input(pulsar::RG_G_DS_VIEW, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_DS_VIEW);
		this->mp_clear_buffers_pass->link_input(pulsar::RG_G_HDR_BUFFER, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_HDR_BUFFER);

		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
			this->mp_clear_buffers_pass->link_input(pulsar::RG_G_G_BUFFERS[i], pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_G_BUFFERS[i]);

		this->add_pass(0u, this->mp_clear_buffers_pass);
	}
	{
		this->mp_g_buffer_pass = new pulsar::g_buffer_pass("g_buffer");

		this->mp_g_buffer_pass->link_input(pulsar::RG_G_DS_VIEW, this->mp_clear_buffers_pass->name() + std::string(".") + pulsar::RG_G_DS_VIEW);
		this->mp_g_buffer_pass->link_input(pulsar::RG_G_VIEWPORT, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_VIEWPORT);
		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
			this->mp_g_buffer_pass->link_input(pulsar::RG_G_G_BUFFERS[i], this->mp_clear_buffers_pass->name() + std::string(".") + pulsar::RG_G_G_BUFFERS[i]);

		this->add_pass(1u, this->mp_g_buffer_pass);
	}
	{
		this->mp_deferred_pass = new pulsar::deferred_pass("deferred");
	
		this->mp_deferred_pass->link_input(pulsar::RG_G_DS_VIEW, this->mp_g_buffer_pass->name() + std::string(".") + pulsar::RG_G_DS_VIEW);
		this->mp_deferred_pass->link_input(pulsar::RG_G_VIEWPORT, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_VIEWPORT);
		this->mp_deferred_pass->link_input(pulsar::RG_G_HDR_BUFFER, this->mp_clear_buffers_pass->name() + std::string(".") + pulsar::RG_G_HDR_BUFFER);
		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
			this->mp_deferred_pass->link_input(pulsar::RG_G_G_BUFFERS[i], this->mp_g_buffer_pass->name() + std::string(".") + pulsar::RG_G_G_BUFFERS[i]);
	
		this->add_pass(2u, this->mp_deferred_pass);
	}
	{
		this->mp_skybox_pass = new pulsar::skybox_pass("skybox");
	
		this->mp_skybox_pass->link_input(pulsar::RG_G_DS_VIEW, this->mp_deferred_pass->name() + std::string(".") + pulsar::RG_G_DS_VIEW);
		this->mp_skybox_pass->link_input(pulsar::RG_G_VIEWPORT, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_VIEWPORT);
		this->mp_skybox_pass->link_input(pulsar::RG_G_HDR_BUFFER, this->mp_deferred_pass->name() + std::string(".") + pulsar::RG_G_HDR_BUFFER);
	
		this->add_pass(3u, this->mp_skybox_pass);
	}
	{
		this->mp_post_effects_pass = new pulsar::post_effects_pass("post_effects");
	
		this->mp_post_effects_pass->link_input(pulsar::RG_G_FRAMEBUFFER, this->mp_clear_buffers_pass->name() + std::string(".") + pulsar::RG_G_FRAMEBUFFER);
		this->mp_post_effects_pass->link_input(pulsar::RG_G_HDR_BUFFER, this->mp_skybox_pass->name() + std::string(".") + pulsar::RG_G_HDR_BUFFER);
		this->mp_post_effects_pass->link_input(pulsar::RG_G_VIEWPORT, pulsar::rg::RG_ROOT + std::string(".") + pulsar::RG_G_VIEWPORT);
	
		this->add_pass(4u, this->mp_post_effects_pass);
	}
	{
		this->mp_present_pass = new pulsar::present_pass("present");
		this->mp_present_pass->link_input(pulsar::RG_G_FRAMEBUFFER, this->mp_post_effects_pass->name() + "." + pulsar::RG_G_FRAMEBUFFER);
		this->add_pass(5u, this->mp_present_pass);
	}

	this->compile();
	this->validate();
}

pulsar::deferred_render_graph::~deferred_render_graph()
{
	{
		delete this->mp_ds_view;
		delete this->mp_hdr_buffer;

		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
			delete this->mp_g_buffers[i];
	}
	{
		delete this->mp_framebuffer_source;
		delete this->mp_ds_view_source;
		delete this->mp_viewport_source;
		delete this->mp_hdr_buffer_source;

		int i = -1;
		while (++i < pulsar::G_BUFFERS_COUNT)
			delete this->mp_g_buffers_sources[i];
	}
	{
		delete this->mp_clear_buffers_pass;
		delete this->mp_g_buffer_pass;
		delete this->mp_deferred_pass;
		delete this->mp_skybox_pass;
		delete this->mp_present_pass;
	}
}
