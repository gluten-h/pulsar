
#include "pulsar_render_graph.h"
#include "window/window.h"
#include "config/render_graph.h"

#include "passes/clear_buffer_pass.h"
#include "passes/present_pass.h"


PULSAR::pulsar_render_graph::pulsar_render_graph()
{
	PULSAR::window &main_window = PULSAR::window::get();

	{
		this->mp_framebuffer = &main_window.framebuffer();
		this->mp_ds_view = new PULSAR::depth_stencil_view;
	}

	{
		XMUINT2 window_size = main_window.size();
		this->mp_ds_view->set(window_size.x, window_size.y);
		main_window.framebuffer().link_buffer_resource(this->mp_ds_view);

		this->mp_framebuffer_source = new PULSAR::rg::buffer_source<PULSAR::framebuffer>(RG_G_FRAMEBUFFER, this->mp_framebuffer);
		this->mp_ds_view_source = new PULSAR::rg::buffer_source<PULSAR::depth_stencil_view>(RG_G_DS_VIEW, this->mp_ds_view);

		this->register_global_source(this->mp_framebuffer_source);
		this->register_global_source(this->mp_ds_view_source);
	}

	//{
	//	this->clear_backbuffer_pass->set_input_linkage("backbuffer", "~.backbuffer");
	//	this->add_pass(this->clear_backbuffer_pass, 0u);
	//}
	//{
	//	this->present_pass->set_input_linkage("backbuffer", "clear_backbuffer.backbuffer");
	//	this->add_pass(this->present_pass, 1u);
	//}

	{
		this->mp_clear_buffer_pass = new PULSAR::clear_buffer_pass("clear_buffer");
		this->mp_clear_buffer_pass->link_input(RG_G_FRAMEBUFFER, std::string("~.") + RG_G_FRAMEBUFFER);
		this->add_pass(0u, this->mp_clear_buffer_pass);
	}
	{
		this->mp_present_pass = new PULSAR::present_pass("present");
		this->mp_present_pass->link_input(RG_G_FRAMEBUFFER, std::string("clear_buffer.") + RG_G_FRAMEBUFFER);
		this->add_pass(1u, this->mp_present_pass);
	}

	this->compile();
	this->validate();
}

PULSAR::pulsar_render_graph::~pulsar_render_graph()
{
	{
		delete this->mp_ds_view;
	}
	{
		delete this->mp_framebuffer_source;
		delete this->mp_ds_view_source;
	}
	{
		delete this->mp_clear_buffer_pass;
		delete this->mp_present_pass;
	}
}
