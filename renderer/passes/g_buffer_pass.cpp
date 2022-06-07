
#include "g_buffer_pass.h"
#include "gfx/gfx.h"
#include "exceptions/rg_exception.h"
#include "config/config.h"
#include "config/shader.h"
#include "config/rasterizer_state.h"
#include "renderer/renderer.h"
#include "depth_stencil/depth_stencil_state.h"
#include "shaders/vert_shader.h"
#include "shaders/geom_shader.h"
#include "input_layout/input_layout.h"
#include "sampler/sampler.h"
#include "depth_stencil/depth_stencil_view.h"
#include "viewport/viewport.h"
#include "render_texture/render_texture.h"
#include "render_queue/render_queue.h"
#include "render_queue/job.h"
#include "scene/scene.h"


pulsar::g_buffer_pass::g_buffer_pass(const std::string &name) : pulsar::rg::pass(name)
{
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	this->mp_ds_state = new pulsar::depth_stencil_state(TRUE, D3D11_COMPARISON_LESS, D3D11_DEPTH_WRITE_MASK_ALL);
	this->mp_g_buffer_vs = new pulsar::vert_shader(pulsar::G_BUFFER_VS_PATH);
	this->mp_g_buffer_gs = new pulsar::geom_shader(pulsar::G_BUFFER_GS_PATH);
	this->mp_input_layout = new pulsar::input_layout(this->mp_g_buffer_vs->get_shader_blob(), ied, (UINT)std::size(ied));
	this->mp_sampler = new pulsar::sampler(pulsar::G_BUFFER_FRAG_SAMPLER_SLOT);

	this->mp_ds_view_input = new pulsar::rg::buffer_input<pulsar::depth_stencil_view>(pulsar::RG_G_DS_VIEW, this->mp_ds_view);
	this->mp_ds_view_source = new pulsar::rg::buffer_source<pulsar::depth_stencil_view>(pulsar::RG_G_DS_VIEW, this->mp_ds_view);

	this->register_input(this->mp_ds_view_input);
	this->register_source(this->mp_ds_view_source);

	int i = -1;
	while (++i < pulsar::G_BUFFERS_COUNT)
	{
		this->mp_g_buffers_inputs[i] = new pulsar::rg::buffer_input<pulsar::render_texture>(pulsar::RG_G_G_BUFFERS[i], this->mp_g_buffers[i]);
		this->mp_g_buffers_sources[i] = new pulsar::rg::buffer_source<pulsar::render_texture>(pulsar::RG_G_G_BUFFERS[i], this->mp_g_buffers[i]);

		this->register_input(this->mp_g_buffers_inputs[i]);
		this->register_source(this->mp_g_buffers_sources[i]);
	}
}

pulsar::g_buffer_pass::~g_buffer_pass()
{
	delete this->mp_ds_state;
	delete this->mp_g_buffer_vs;
	delete this->mp_g_buffer_gs;
	delete this->mp_input_layout;
	delete this->mp_sampler;

	delete this->mp_ds_view_input;
	delete this->mp_ds_view_source;

	int i = -1;
	while (++i < pulsar::G_BUFFERS_COUNT)
	{
		delete this->mp_g_buffers_inputs[i];
		delete this->mp_g_buffers_sources[i];
	}
}

void	pulsar::g_buffer_pass::validate() const
{
	if (!this->mp_ds_view)
		THROW_RG_EXC("Depth Stencil View isn't bound");

	int i = -1;
	while (++i < pulsar::G_BUFFERS_COUNT)
	{
		if (!this->mp_g_buffers[i])
			THROW_RG_EXC("G-Buffer isn't bound");
	}
}

void	pulsar::g_buffer_pass::execute()
{
	ID3D11DeviceContext *device_context = pulsar::gfx::instance().device_context();
	pulsar::renderer &renderer = pulsar::renderer::instance();
	pulsar::scene *active_scene = pulsar::scene::get_active_scene();

	if (!active_scene || !active_scene->get_main_camera())
		return;

	ID3D11RenderTargetView *g_buffers_null[pulsar::G_BUFFERS_COUNT] = { NULL };
	ID3D11RenderTargetView *g_buffers_data[pulsar::G_BUFFERS_COUNT];

	int i = -1;
	while (++i < pulsar::G_BUFFERS_COUNT)
		g_buffers_data[i] = this->mp_g_buffers[i]->render_target();

	auto *camera_viewport = renderer.get_main_camera_viewport();
	auto *vert_camera_cbuffer = renderer.get_vert_camera_cbuffer();

	{
		pulsar::BACK_FACE_CULL_RS.bind();
		this->mp_ds_state->bind();
		this->mp_g_buffer_vs->bind();
		this->mp_g_buffer_gs->bind();
		this->mp_input_layout->bind();
		this->mp_sampler->bind();
		camera_viewport->bind();
		device_context->OMSetRenderTargets(pulsar::G_BUFFERS_COUNT, g_buffers_data, this->mp_ds_view->get_view());

		vert_camera_cbuffer->set_slot(pulsar::G_BUFFER_VERT_CAMERA_SLOT);
		vert_camera_cbuffer->bind();
	}

	pulsar::render_queue::instance().execute();

	{
		vert_camera_cbuffer->unbind();

		device_context->OMSetRenderTargets(pulsar::G_BUFFERS_COUNT, g_buffers_null, NULL);
		camera_viewport->unbind();
		this->mp_sampler->unbind();
		this->mp_input_layout->unbind();
		this->mp_g_buffer_gs->unbind();
		this->mp_g_buffer_vs->unbind();
		this->mp_ds_state->unbind();
		pulsar::BACK_FACE_CULL_RS.unbind();
	}
}
