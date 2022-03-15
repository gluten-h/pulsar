#pragma once

#include "bindable.h"
#include "bindable_entity.h"


namespace PULSAR
{
	class RENDER_TARGET : public PULSAR::BINDABLE, public PULSAR::BUFFER_RESOURCE
	{
	private:
		IDXGISwapChain				*swap_chain = NULL;
		ID3D11Texture2D				*back_buffer_texture = NULL;
		ID3D11RenderTargetView		*back_buffer = NULL;

		mutable ID3D11DepthStencilView		*ds_view = NULL;


		void	set_rt_memory(HWND hwnd, BOOL windowed);

		void	remove_swap_chain();
		void	remove_back_buffer_texture();
		void	remove_back_buffer();
		void	remove_rt_memory();

		void	copy_assign(const RENDER_TARGET &rt);

	protected:
		void	remove_from_entities() override
		{
			for (auto &it : this->entities)
				it->_remove_bindable_ignore_entity(this);
			this->entities.clear();
		}

	public:
		using PULSAR::BINDABLE::bind;

	public:
		RENDER_TARGET	&operator=(const RENDER_TARGET &rt);
		RENDER_TARGET(const RENDER_TARGET &rt);
		RENDER_TARGET();
		RENDER_TARGET(HWND hwnd, BOOL windowed = TRUE);
		~RENDER_TARGET();

		void	set(HWND hwnd, BOOL windowed = TRUE);
		void	set_ds_view(ID3D11DepthStencilView *ds_view);

		void	clear() override;
		void	present();

		static RENDER_TARGET	*create();

		void	bind() const override
		{
			this->device_context->OMSetRenderTargets(1u, &this->back_buffer, this->ds_view);
			BINDABLE::add_unbind(*this);
		}

		void	unbind() const override
		{
			static ID3D11RenderTargetView *null_ptr[1] = { NULL };
			this->device_context->OMSetRenderTargets(1u, null_ptr, NULL);
			this->ds_view = NULL;
		}

	};
}
