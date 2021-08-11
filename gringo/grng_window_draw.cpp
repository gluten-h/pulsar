
#include "grng_window.h"


void		grng_window::draw_g_pass()
{
	this->deferred_buffer.bind_rtv();
	this->curr_scene->draw();

	GRNG_BINDABLE::unbind_all();
}

void		grng_window::draw_deferred()
{
	GRNG_STD_BACK_FACE_CULL_RS.bind();
	
	ID3D11RenderTargetView *rt_hdr = this->deferred_buffer.get_hdr_buffer().get_render_target();
	this->device_context->OMSetRenderTargets(1u, &rt_hdr, NULL);
	this->deferred_buffer.bind_srv();
	this->curr_scene->bind();
	this->device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->device_context->Draw(4u, 0u);

	GRNG_BINDABLE::unbind_all();
}

void		grng_window::draw_skybox()
{
	ID3D11RenderTargetView *rt_hdr = this->deferred_buffer.get_hdr_buffer().get_render_target();
	this->device_context->OMSetRenderTargets(1u, &rt_hdr, this->deferred_buffer.get_ds_view().get_view());
	this->deferred_buffer.get_viewport().bind(GRNG_BIND_SCOPE::GLOBAL);
	this->skybox_ds_state.bind(GRNG_BIND_SCOPE::GLOBAL);
	this->curr_scene->draw_skybox();

	GRNG_BINDABLE::unbind_all();
}

void		grng_window::draw_post_effects()
{
	GRNG_STD_BACK_FACE_CULL_RS.bind();
	this->render_target.bind(GRNG_BIND_SCOPE::GLOBAL);
	this->deferred_buffer.bind_post_effects();
	this->device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->device_context->Draw(4u, 0u);

	GRNG_BINDABLE::unbind_all();
}

void		grng_window::draw()
{
	if (!this->curr_camera || !this->curr_scene)
		return;

	D3D11_VIEWPORT &viewport = this->deferred_buffer.get_viewport().get();
	this->curr_camera->update(viewport.Width, viewport.Height);

	this->draw_g_pass();
	this->draw_deferred();
	this->draw_skybox();
	this->draw_post_effects();
}


void		grng_window::present()
{
	this->render_target.present();
}
