
#include "grng_window.h"


void		grng_window::draw_g_pass()
{
	this->deferred_buffer.bind_as_rtv();

	D3D11_VIEWPORT &viewport = this->deferred_buffer.get_viewport();
	this->curr_camera->update(viewport.Width, viewport.Height);

	this->curr_scene->draw();
}

void		grng_window::draw_deferred()
{
	GRNG_STD_BACK_FACE_CULL_RS.bind();
	this->device_context->OMSetRenderTargets(1, &this->back_buffer, NULL);
	this->device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->deferred_buffer.bind_as_srv();
	this->curr_scene->bind();
	this->device_context->Draw(4u, 0u);
}

void		grng_window::draw_skybox()
{
	this->device_context->OMSetRenderTargets(1, &this->back_buffer, this->deferred_buffer.get_ds_view().get_view());
	this->skybox_ds_state.bind();

	this->curr_scene->draw_skybox();
}

void		grng_window::draw()
{
	if (!this->curr_camera || !this->curr_scene)
		return;

	this->draw_g_pass();
	this->draw_deferred();
	this->draw_skybox();
}


void		grng_window::present()
{
	this->swap_chain->Present(1u, 0u);
}
