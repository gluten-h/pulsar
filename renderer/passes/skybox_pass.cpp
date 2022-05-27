
#include "skybox_pass.h"
#include "config/config.h"
#include "config/rasterizer_state.h"
#include "config/mesh.h"
#include "renderer/renderer.h"
#include "shaders/vert_shader.h"
#include "shaders/frag_shader.h"
#include "depth_stencil/depth_stencil_state.h"
#include "sampler/sampler.h"
#include "input_layout/input_layout.h"
#include "render_texture/render_texture.h"
#include "depth_stencil/depth_stencil_view.h"
#include "viewport/viewport.h"
#include "scene/scene.h"


pulsar::skybox_pass::skybox_pass(const std::string &name) : pulsar::rg::pass(name)
{
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	this->mp_skybox_vs = new pulsar::vert_shader(pulsar::SKYBOX_VS_PATH);
	this->mp_skybox_fs = new pulsar::frag_shader(pulsar::SKYBOX_FS_PATH);
	this->mp_ds_state = new pulsar::depth_stencil_state(TRUE, D3D11_COMPARISON_LESS_EQUAL, D3D11_DEPTH_WRITE_MASK_ZERO);
	this->mp_sampler = new pulsar::sampler(pulsar::SKYBOX_FRAG_SAMPLER_SLOT);
	this->mp_input_layout = new pulsar::input_layout(this->mp_skybox_vs->get_shader_blob(), ied, (UINT)std::size(ied));

	this->mp_hdr_buffer_input = new pulsar::rg::buffer_input<pulsar::render_texture>(pulsar::RG_G_HDR_BUFFER, this->mp_hdr_buffer);
	this->mp_hdr_buffer_source = new pulsar::rg::buffer_source<pulsar::render_texture>(pulsar::RG_G_HDR_BUFFER, this->mp_hdr_buffer);

	this->mp_ds_view_input = new pulsar::rg::buffer_input<pulsar::depth_stencil_view>(pulsar::RG_G_DS_VIEW, this->mp_ds_view);
	this->mp_ds_view_source = new pulsar::rg::buffer_source<pulsar::depth_stencil_view>(pulsar::RG_G_DS_VIEW, this->mp_ds_view);

	this->mp_viewport_input = new pulsar::rg::bindable_input<pulsar::viewport>(pulsar::RG_G_VIEWPORT, this->mp_viewport);

	this->register_input(this->mp_hdr_buffer_input);
	this->register_source(this->mp_hdr_buffer_source);

	this->register_input(this->mp_ds_view_input);
	this->register_source(this->mp_ds_view_source);

	this->register_input(this->mp_viewport_input);
}

pulsar::skybox_pass::~skybox_pass()
{
	delete this->mp_skybox_vs;
	delete this->mp_skybox_fs;
	delete this->mp_ds_state;
	delete this->mp_sampler;
	delete this->mp_input_layout;

	delete this->mp_hdr_buffer_input;
	delete this->mp_hdr_buffer_source;

	delete this->mp_ds_view_input;
	delete this->mp_ds_view_source;

	delete this->mp_viewport_input;
}

void	pulsar::skybox_pass::validate() const
{
	if (!this->mp_hdr_buffer)
		THROW_RG_EXC("HDR Buffer isn't bound");
	if (!this->mp_ds_view)
		THROW_RG_EXC("Depth Stencil View isn't bound");
	if (!this->mp_viewport)
		THROW_RG_EXC("Viewport isn't bound");
}

void	pulsar::skybox_pass::execute()
{
	pulsar::renderer &renderer = pulsar::renderer::instance();
	pulsar::scene *active_scene = pulsar::scene::get_active_scene();

	if (!active_scene || !active_scene->get_main_camera())
		return;

	auto *vert_camera_cbuffer = renderer.get_vert_camera_cbuffer();
	auto *frag_camera_cbuffer = renderer.get_frag_camera_cbuffer();
	auto &skybox_material = active_scene->skybox_material();

	{
		pulsar::FRONT_FACE_CULL_RS.bind();
		pulsar::CUBE.bind();
		this->mp_skybox_vs->bind();
		this->mp_skybox_fs->bind();
		this->mp_ds_state->bind();
		this->mp_sampler->bind();
		this->mp_input_layout->bind();
		this->mp_viewport->bind();
		this->mp_hdr_buffer->bind_rtv(this->mp_ds_view->get_view());

		vert_camera_cbuffer->set_slot(pulsar::SKYBOX_VERT_CAMERA_SLOT);
		vert_camera_cbuffer->bind();
		skybox_material.bind();
		frag_camera_cbuffer->set_slot(pulsar::SKYBOX_FRAG_CAMERA_SLOT);
		frag_camera_cbuffer->bind();
	}

	pulsar::gfx::instance().draw_indexed(pulsar::CUBE.get_index_count());

	{
		frag_camera_cbuffer->unbind();
		skybox_material.unbind();
		vert_camera_cbuffer->unbind();

		this->mp_hdr_buffer->unbind_rtv();
		this->mp_viewport->unbind();
		this->mp_input_layout->unbind();
		this->mp_sampler->unbind();
		this->mp_ds_state->unbind();
		this->mp_skybox_fs->unbind();
		this->mp_skybox_vs->bind();
		pulsar::CUBE.unbind();
		pulsar::FRONT_FACE_CULL_RS.unbind();
	}
}
