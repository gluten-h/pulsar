
#include "g_buffer_pass.h"
#include "gfx/gfx.h"
#include "exceptions/rg_exception.h"
#include "depth_stencil/depth_stencil_state.h"
#include "depth_stencil/depth_stencil_view.h"
#include "viewport/viewport.h"
#include "render_texture/render_texture.h"
#include "render_queue/render_queue.h"
#include "render_queue/job.h"


PULSAR::g_buffer_pass::g_buffer_pass(const std::string &name) : PULSAR::render_queue_pass(name)
{
	this->mp_ds_state = new PULSAR::depth_stencil_state(TRUE, D3D11_COMPARISON_LESS, D3D11_DEPTH_WRITE_MASK_ALL);

	this->mp_ds_view_input = new PULSAR::rg::buffer_input<PULSAR::depth_stencil_view>(PULSAR::RG_G_DS_VIEW, this->mp_ds_view);
	this->mp_ds_view_source = new PULSAR::rg::buffer_source<PULSAR::depth_stencil_view>(PULSAR::RG_G_DS_VIEW, this->mp_ds_view);

	this->mp_viewport_input = new PULSAR::rg::bindable_input<PULSAR::viewport>(PULSAR::RG_G_VIEWPORT, this->mp_viewport);
	this->mp_viewport_source = new PULSAR::rg::bindable_source<PULSAR::viewport>(PULSAR::RG_G_VIEWPORT, this->mp_viewport);

	this->register_input(this->mp_ds_view_input);
	this->register_source(this->mp_ds_view_source);

	this->register_input(this->mp_viewport_input);
	this->register_source(this->mp_viewport_source);

	int i = -1;
	while (++i < PULSAR::G_BUFFERS_COUNT)
	{
		this->mp_g_buffers_inputs[i] = new PULSAR::rg::buffer_input<PULSAR::render_texture>(PULSAR::RG_G_G_BUFFERS[i], this->mp_g_buffers[i]);
		this->mp_g_buffers_sources[i] = new PULSAR::rg::buffer_source<PULSAR::render_texture>(PULSAR::RG_G_G_BUFFERS[i], this->mp_g_buffers[i]);

		this->register_input(this->mp_g_buffers_inputs[i]);
		this->register_source(this->mp_g_buffers_sources[i]);
	}
}

PULSAR::g_buffer_pass::~g_buffer_pass()
{
	delete this->mp_ds_state;

	delete this->mp_ds_view_input;
	delete this->mp_ds_view_source;

	delete this->mp_viewport_input;
	delete this->mp_viewport_source;

	int i = -1;
	while (++i < PULSAR::G_BUFFERS_COUNT)
	{
		delete this->mp_g_buffers_inputs[i];
		delete this->mp_g_buffers_sources[i];
	}
}

void	PULSAR::g_buffer_pass::validate() const
{
	if (!this->mp_ds_view)
		THROW_RG_EXC("Depth Stencil View isn't bound");
	if (!this->mp_viewport)
		THROW_RG_EXC("Viewport isn't bound");
	
	int i = -1;
	while (++i < PULSAR::G_BUFFERS_COUNT)
	{
		if (!this->mp_g_buffers[i])
			THROW_RG_EXC("G-Buffer isn't bound");
	}
}

void	PULSAR::g_buffer_pass::execute(float delta_time)
{
	//this->mp_ds_view->bind();
	//PULSAR::render_queue::get().execute();

	ID3D11RenderTargetView *g_buffers_data[PULSAR::G_BUFFERS_COUNT];

	int i = -1;
	while (++i < PULSAR::G_BUFFERS_COUNT)
		g_buffers_data[i] = this->mp_g_buffers[i]->render_target();

	//this->mp_ds_state->bind();
	//this->mp_viewport->bind();
	//PULSAR::gfx::get().device_context()->OMSetRenderTargets(PULSAR::G_BUFFERS_COUNT, g_buffers_data, this->mp_ds_view->get_view());
}
