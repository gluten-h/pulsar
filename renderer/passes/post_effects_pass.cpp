
#include "post_effects_pass.h"
#include "config/config.h"
#include "renderer/renderer.h"
#include "shaders/frag_shader.h"
#include "sampler/sampler.h"
#include "framebuffer/framebuffer.h"
#include "render_texture/render_texture.h"
#include "viewport/viewport.h"
#include "scene/scene.h"


pulsar::post_effects_pass::post_effects_pass(const std::string &name) : pulsar::fullscreen_pass(name)
{
	this->mp_post_effects_fs = new pulsar::frag_shader(pulsar::POST_EFFECTS_FS_PATH);
	this->mp_sampler = new pulsar::sampler(pulsar::POST_EFFECTS_FRAG_SAMPLER_SLOT);

	this->mp_frambuffer_input = new pulsar::rg::buffer_input<pulsar::framebuffer>(pulsar::RG_G_FRAMEBUFFER, this->mp_framebuffer);
	this->mp_framebuffer_source = new pulsar::rg::buffer_source<pulsar::framebuffer>(pulsar::RG_G_FRAMEBUFFER, this->mp_framebuffer);

	this->mp_hdr_buffer_input = new pulsar::rg::buffer_input<pulsar::render_texture>(pulsar::RG_G_HDR_BUFFER, this->mp_hdr_buffer);
	this->mp_hdr_buffer_source = new pulsar::rg::buffer_source<pulsar::render_texture>(pulsar::RG_G_HDR_BUFFER, this->mp_hdr_buffer);

	this->mp_viewport_input = new pulsar::rg::bindable_input<pulsar::viewport>(pulsar::RG_G_VIEWPORT, this->mp_viewport);

	this->register_input(this->mp_frambuffer_input);
	this->register_source(this->mp_framebuffer_source);

	this->register_input(this->mp_hdr_buffer_input);
	this->register_source(this->mp_hdr_buffer_source);

	this->register_input(this->mp_viewport_input);
}

pulsar::post_effects_pass::~post_effects_pass()
{
	delete this->mp_post_effects_fs;
	delete this->mp_sampler;

	delete this->mp_frambuffer_input;
	delete this->mp_framebuffer_source;

	delete this->mp_hdr_buffer_input;
	delete this->mp_hdr_buffer_source;

	delete this->mp_viewport_input;
}

void	pulsar::post_effects_pass::validate() const
{
	if (!this->mp_framebuffer)
		THROW_RG_EXC("Framebuffer isn't bound");
	if (!this->mp_hdr_buffer)
		THROW_RG_EXC("HDR Buffer isn't bound");
	if (!this->mp_viewport)
		THROW_RG_EXC("Viewport isn't bound");
}

void	pulsar::post_effects_pass::execute()
{
	pulsar::renderer &renderer = pulsar::renderer::instance();
	pulsar::scene *active_scene = pulsar::scene::get_active_scene();

	if (!active_scene || !active_scene->get_main_camera())
		return;

	auto *frag_camera_cbuffer = renderer.get_frag_camera_cbuffer();

	{
		this->mp_post_effects_fs->bind();
		this->mp_sampler->bind();
		this->mp_viewport->bind();
		this->mp_hdr_buffer->bind_srv();
		this->mp_framebuffer->bind();

		frag_camera_cbuffer->set_slot(pulsar::POST_EFFECTS_FRAG_CAMERA_SLOT);
		frag_camera_cbuffer->bind();
	}

	pulsar::fullscreen_pass::execute();

	{
		frag_camera_cbuffer->unbind();

		this->mp_framebuffer->unbind();
		this->mp_hdr_buffer->unbind_srv();
		this->mp_viewport->unbind();
		this->mp_sampler->unbind();
		this->mp_post_effects_fs->unbind();
	}
}
