
#include "grng_window.h"


void		grng_window::draw_g_pass()
{
	if (!this->curr_camera || !this->curr_scene)
		return;

	this->deferred_buffer.bind_as_rtv();

	D3D11_VIEWPORT &viewport = this->deferred_buffer.get_viewport();
	this->curr_camera->update(viewport.Width, viewport.Height);

	this->curr_scene->draw();
}

void		grng_window::draw_deferred()
{
	if (!this->curr_camera || !this->curr_scene)
		return;

	this->device_context->OMSetRenderTargets(1, &this->back_buffer, this->deferred_buffer.get_depth_stencil().get_ds_view());
	this->device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->deferred_buffer.bind_as_srv();
	this->curr_scene->bind();
	this->device_context->Draw(4u, 0u);
}

void		grng_window::present()
{
	this->swap_chain->Present(1u, 0u);
}
