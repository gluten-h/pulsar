//
//#include "window.h"
//
//
//void		PULSAR::WINDOW::draw_g_pass()
//{
//	this->deferred_buffer.bind_rtv();
//	this->curr_scene->draw();
//
//	static ID3D11RenderTargetView *null_ptr[G_BUFFER_COUNT] = { NULL, NULL, NULL, NULL };
//	this->device_context->OMSetRenderTargets(G_BUFFER_COUNT, null_ptr, NULL);
//
//	PULSAR::BINDABLE::unbind_all();
//}
//
//void		PULSAR::WINDOW::draw_deferred()
//{
//	PULSAR::STD_BACK_FACE_CULL_RS.bind();
//	
//	//ID3D11RenderTargetView *rt_hdr = this->deferred_buffer.get_hdr_buffer().get_render_target();
//	//this->device_context->OMSetRenderTargets(1u, &rt_hdr, NULL);
//
//	//this->deferred_buffer.get_hdr_buffer().set_mode(PULSAR::BIND_MODE::RTV);
//	//this->deferred_buffer.get_hdr_buffer().bind(PULSAR::BIND_SCOPE::GLOBAL);
//
//	this->deferred_buffer.bind_srv();
//	this->curr_scene->bind();
//	this->device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	this->device_context->Draw(4u, 0u);
//
//	static ID3D11RenderTargetView *null_ptr[G_BUFFER_COUNT] = { NULL, NULL, NULL, NULL };
//	this->device_context->OMSetRenderTargets(G_BUFFER_COUNT, null_ptr, NULL);
//
//	PULSAR::BINDABLE::unbind_all();
//}
//
//void		PULSAR::WINDOW::draw_skybox()
//{
//	//ID3D11RenderTargetView *rt_hdr = this->deferred_buffer.get_hdr_buffer().get_render_target();
//	//this->device_context->OMSetRenderTargets(1u, &rt_hdr, this->deferred_buffer.get_ds_view().get_view());
//
//	this->deferred_buffer.get_hdr_buffer().set_mode(PULSAR::BIND_MODE::RTV);
//	this->deferred_buffer.get_hdr_buffer().set_ds_view(this->deferred_buffer.get_ds_view().get_view());
//	this->deferred_buffer.get_hdr_buffer().bind(PULSAR::BIND_SCOPE::GLOBAL);
//
//	this->skybox_ds_state.bind(PULSAR::BIND_SCOPE::GLOBAL);
//	this->deferred_buffer.get_viewport().bind(PULSAR::BIND_SCOPE::GLOBAL);
//	this->curr_scene->draw_skybox();
//
//	PULSAR::BINDABLE::unbind_all();
//}
//
//void		PULSAR::WINDOW::draw_post_effects()
//{
//	PULSAR::STD_BACK_FACE_CULL_RS.bind();
//	this->render_target.bind(PULSAR::BIND_SCOPE::GLOBAL);
//	this->deferred_buffer.bind_post_effects();
//	this->device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	this->device_context->Draw(4u, 0u);
//
//	PULSAR::BINDABLE::unbind_all();
//}
//
//void		PULSAR::WINDOW::draw()
//{
//	if (!this->curr_camera || !this->curr_scene)
//		return;
//
//	D3D11_VIEWPORT &viewport = this->deferred_buffer.get_viewport().get();
//	this->curr_camera->update(viewport.Width, viewport.Height);
//
//	//this->rg->execute();
//
//	this->draw_g_pass();
//	this->draw_deferred();
//	this->draw_skybox();
//	this->draw_post_effects();
//}
//
//
//void		PULSAR::WINDOW::present()
//{
//	this->render_target.present();
//}
