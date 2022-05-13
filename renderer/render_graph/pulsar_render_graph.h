#pragma once

//#include "render_graph.h"
//
//#include "buffer_clear_pass.h"
//#include "present_pass.h"
//
//
//class rg : public PULSAR::RENDER_GRAPH
//{
//private:
//	PULSAR::BUFFER_CLEAR_PASS	*clear_backbuffer_pass = PULSAR::BUFFER_CLEAR_PASS::create("clear_backbuffer");
//	PULSAR::PRESENT_PASS		*present_pass = PULSAR::PRESENT_PASS::create("present");
//
//
//public:
//	rg(PULSAR::RENDER_TARGET *backbuffer, PULSAR::DEPTH_STENCIL_VIEW *depth_stencil_view) : PULSAR::RENDER_GRAPH(backbuffer, depth_stencil_view)
//	{
//		{
//			this->clear_backbuffer_pass->set_input_linkage("backbuffer", "~.backbuffer");
//			this->add_pass(this->clear_backbuffer_pass, 0u);
//		}
//		{
//			this->present_pass->set_input_linkage("backbuffer", "clear_backbuffer.backbuffer");
//			this->add_pass(this->present_pass, 1u);
//		}
//		this->compile();
//		this->validate();
//	}
//	~rg()
//	{
//		this->clear_backbuffer_pass->destroy();
//		this->present_pass->destroy();
//	}
//
//	static rg	*create(PULSAR::RENDER_TARGET *backbuffer, PULSAR::DEPTH_STENCIL_VIEW *depth_stencil_view)
//	{
//		return ((rg*)PULSAR::RG_COMPONENT::add_to_manager(new rg(backbuffer, depth_stencil_view)));
//	}
//};

#include "rg/render_graph.h"
#include "rg/buffer_source.h"
#include "depth_stencil/depth_stencil_view.h"


namespace PULSAR
{
	class framebuffer;

	class clear_buffer_pass;
	class present_pass;

	class pulsar_render_graph : public PULSAR::rg::render_graph
	{
	private:
		PULSAR::framebuffer *mp_framebuffer = NULL;
		PULSAR::depth_stencil_view *mp_ds_view = NULL;

		PULSAR::rg::buffer_source<PULSAR::framebuffer> *mp_framebuffer_source = NULL;
		PULSAR::rg::buffer_source<PULSAR::depth_stencil_view> *mp_ds_view_source = NULL;

		PULSAR::clear_buffer_pass *mp_clear_buffer_pass = NULL;
		PULSAR::present_pass *mp_present_pass = NULL;

	public:
		pulsar_render_graph &operator=(const pulsar_render_graph&) = delete;
		pulsar_render_graph &operator=(pulsar_render_graph&&) = delete;
		pulsar_render_graph(const pulsar_render_graph&) = delete;
		pulsar_render_graph(pulsar_render_graph&&) = delete;
		pulsar_render_graph();
		~pulsar_render_graph();
	};
}
