
#include "clear_buffers_pass.h"
#include "config/render_graph.h"
#include "exceptions/rg_exception.h"
#include "framebuffer/framebuffer.h"
#include "depth_stencil/depth_stencil_view.h"
#include "render_texture/render_texture.h"


PULSAR::clear_buffers_pass::clear_buffers_pass(const std::string &name) : PULSAR::rg::pass(name)
{
	this->mp_framebuffer_input = new PULSAR::rg::buffer_input<PULSAR::framebuffer>(PULSAR::RG_G_FRAMEBUFFER, this->mp_framebuffer);
	this->mp_frambuffer_source = new PULSAR::rg::buffer_source<PULSAR::framebuffer>(PULSAR::RG_G_FRAMEBUFFER, this->mp_framebuffer);

	this->mp_ds_view_input = new PULSAR::rg::buffer_input<PULSAR::depth_stencil_view>(PULSAR::RG_G_DS_VIEW, this->mp_ds_view);
	this->mp_ds_view_source = new PULSAR::rg::buffer_source<PULSAR::depth_stencil_view>(PULSAR::RG_G_DS_VIEW, this->mp_ds_view);

	this->register_input(this->mp_framebuffer_input);
	this->register_source(this->mp_frambuffer_source);

	this->register_input(this->mp_ds_view_input);
	this->register_source(this->mp_ds_view_source);

	int i = -1;
	while (++i < PULSAR::G_BUFFERS_COUNT)
	{
		this->mp_g_buffers_inputs[i] = new PULSAR::rg::buffer_input<PULSAR::render_texture>(PULSAR::RG_G_G_BUFFERS[i], this->mp_g_buffers[i]);
		this->mp_g_buffers_sources[i] = new PULSAR::rg::buffer_source<PULSAR::render_texture>(PULSAR::RG_G_G_BUFFERS[i], this->mp_g_buffers[i]);

		this->register_input(this->mp_g_buffers_inputs[i]);
		this->register_source(this->mp_g_buffers_sources[i]);
	}
}

PULSAR::clear_buffers_pass::~clear_buffers_pass()
{
	delete this->mp_framebuffer_input;
	delete this->mp_frambuffer_source;

	delete this->mp_ds_view_input;
	delete this->mp_ds_view_source;

	int i = -1;
	while (++i < PULSAR::G_BUFFERS_COUNT)
	{
		delete this->mp_g_buffers_inputs[i];
		delete this->mp_g_buffers_sources[i];
	}
}

void	PULSAR::clear_buffers_pass::validate() const
{
	if (!this->mp_framebuffer)
		THROW_RG_EXC("Framebuffer isn't bound");
	if (!this->mp_ds_view)
		THROW_RG_EXC("Depth Stencil View isn't bound");

	int i = -1;
	while (++i < PULSAR::G_BUFFERS_COUNT)
	{
		if (!this->mp_g_buffers[i])
			THROW_RG_EXC("G-Buffer isn't bound");
	}
}

void	PULSAR::clear_buffers_pass::execute(float delta_time)
{
	this->mp_framebuffer->clear();
	this->mp_ds_view->clear();

	int i = -1;
	while (++i < PULSAR::G_BUFFERS_COUNT)
		this->mp_g_buffers[i]->clear();
}
