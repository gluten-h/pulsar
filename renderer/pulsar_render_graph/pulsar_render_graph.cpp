
#include "pulsar_render_graph.h"
#include "render_graph/rg_const.h"
#include "exceptions/rg_exception.h"
#include "framebuffer/framebuffer.h"
#include "depth_stencil/depth_stencil_view.h"
#include "viewport/viewport.h"
#include "render_texture/render_texture.h"

#include "passes/clear_buffers_pass.h"
#include "passes/g_buffer_pass.h"
#include "passes/present_pass.h"


PULSAR::pulsar_render_graph::pulsar_render_graph(PULSAR::framebuffer &framebuffer)
{
	{
		XMUINT2 framebuffer_size = framebuffer.size();

		this->mp_framebuffer = &framebuffer;
		this->mp_ds_view = new PULSAR::depth_stencil_view(framebuffer_size.x, framebuffer_size.y);
		this->mp_viewport = new PULSAR::viewport(framebuffer_size.x, framebuffer_size.y);

		framebuffer.link_buffer_resource(this->mp_ds_view);
		framebuffer.link_buffer_resource(this->mp_viewport);

		int i = -1;
		while (++i < PULSAR::G_BUFFERS_COUNT)
		{
			this->mp_g_buffers[i] = new PULSAR::render_texture(framebuffer_size.x, framebuffer_size.y, DXGI_FORMAT_R16G16B16A16_FLOAT, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE, 0u);
			this->mp_g_buffers[i]->set_slot(i);
			framebuffer.link_buffer_resource(this->mp_g_buffers[i]);
		}
	}

	{
		this->mp_framebuffer_source = new PULSAR::rg::buffer_source<PULSAR::framebuffer>(PULSAR::RG_G_FRAMEBUFFER, this->mp_framebuffer);
		this->mp_ds_view_source = new PULSAR::rg::buffer_source<PULSAR::depth_stencil_view>(PULSAR::RG_G_DS_VIEW, this->mp_ds_view);
		this->mp_viewport_source = new PULSAR::rg::bindable_source<PULSAR::viewport>(PULSAR::RG_G_VIEWPORT, this->mp_viewport);

		this->register_global_source(this->mp_framebuffer_source);
		this->register_global_source(this->mp_ds_view_source);
		this->register_global_source(this->mp_viewport_source);

		int i = -1;
		while (++i < PULSAR::G_BUFFERS_COUNT)
		{
			this->mp_g_buffers_sources[i] = new PULSAR::rg::buffer_source<PULSAR::render_texture>(PULSAR::RG_G_G_BUFFERS[i], this->mp_g_buffers[i]);
			this->register_global_source(this->mp_g_buffers_sources[i]);
		}
	}

	{
		this->mp_clear_buffers_pass = new PULSAR::clear_buffers_pass("clear_buffers");

		this->mp_clear_buffers_pass->link_input(PULSAR::RG_G_FRAMEBUFFER, PULSAR::rg::RG_ROOT + std::string(".") + PULSAR::RG_G_FRAMEBUFFER);
		this->mp_clear_buffers_pass->link_input(PULSAR::RG_G_DS_VIEW, PULSAR::rg::RG_ROOT + std::string(".") + PULSAR::RG_G_DS_VIEW);
		int i = -1;
		while (++i < PULSAR::G_BUFFERS_COUNT)
			this->mp_clear_buffers_pass->link_input(PULSAR::RG_G_G_BUFFERS[i], PULSAR::rg::RG_ROOT + std::string(".") + PULSAR::RG_G_G_BUFFERS[i]);

		this->add_pass(0u, this->mp_clear_buffers_pass);
	}
	{
		this->mp_g_buffer_pass = new PULSAR::g_buffer_pass("g_buffer");

		this->mp_g_buffer_pass->link_input(PULSAR::RG_G_DS_VIEW, mp_clear_buffers_pass->name() + std::string(".") + PULSAR::RG_G_DS_VIEW);
		this->mp_g_buffer_pass->link_input(PULSAR::RG_G_VIEWPORT, PULSAR::rg::RG_ROOT + std::string(".") + PULSAR::RG_G_VIEWPORT);
		int i = -1;
		while (++i < PULSAR::G_BUFFERS_COUNT)
			this->mp_g_buffer_pass->link_input(PULSAR::RG_G_G_BUFFERS[i], this->mp_clear_buffers_pass->name() + std::string(".") + PULSAR::RG_G_G_BUFFERS[i]);

		this->add_pass(1u, this->mp_g_buffer_pass);
	}
	{
		this->mp_present_pass = new PULSAR::present_pass("present");
		this->mp_present_pass->link_input(PULSAR::RG_G_FRAMEBUFFER, this->mp_clear_buffers_pass->name() + "." + PULSAR::RG_G_FRAMEBUFFER);
		this->add_pass(2u, this->mp_present_pass);
	}

	this->compile();
	this->validate();
}

PULSAR::pulsar_render_graph::~pulsar_render_graph()
{
	{
		delete this->mp_ds_view;
		delete this->mp_viewport;

		int i = -1;
		while (++i < PULSAR::G_BUFFERS_COUNT)
			delete this->mp_g_buffers[i];
	}
	{
		delete this->mp_framebuffer_source;
		delete this->mp_ds_view_source;
		delete this->mp_viewport_source;

		int i = -1;
		while (++i < PULSAR::G_BUFFERS_COUNT)
			delete this->mp_g_buffers_sources[i];
	}
	{
		delete this->mp_clear_buffers_pass;
		delete this->mp_g_buffer_pass;
		delete this->mp_present_pass;
	}
}
