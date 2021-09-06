#pragma once

#include "bindable.h"
#include "bindable_entity.h"


namespace PULSAR
{
	class DEPTH_STENCIL_STATE : public PULSAR::BINDABLE
	{
	private:
		ID3D11DepthStencilState		*ds_state = NULL;


		void		set_ds_memory(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask);
		void		remove_ds_memory();

		void		copy_assign(const DEPTH_STENCIL_STATE &dss);

	protected:
		void		remove_from_entities() override
		{
			for (auto &it : this->entities)
				it->_remove_bindable_ignore_entity(this);
			this->entities.clear();
		}

	public:
		using PULSAR::BINDABLE::bind;

	public:
		DEPTH_STENCIL_STATE		&operator=(const DEPTH_STENCIL_STATE &dss);
		DEPTH_STENCIL_STATE(const DEPTH_STENCIL_STATE &dss);
		DEPTH_STENCIL_STATE(BOOL depth_enable = TRUE, D3D11_COMPARISON_FUNC depth_comp_func = D3D11_COMPARISON_LESS, D3D11_DEPTH_WRITE_MASK depth_write_mask = D3D11_DEPTH_WRITE_MASK_ALL);
		~DEPTH_STENCIL_STATE();

		void						set(BOOL depth_enable, D3D11_COMPARISON_FUNC depth_comp_func, D3D11_DEPTH_WRITE_MASK depth_write_mask);
		ID3D11DepthStencilState		*get_state();

		static DEPTH_STENCIL_STATE		*create();

		void	bind() const override
		{
			this->device_context->OMSetDepthStencilState(this->ds_state, 1u);
			BINDABLE::add_unbind(*this);
		}

		void	unbind() const override
		{
			this->device_context->OMSetDepthStencilState(NULL, 1u);
		}
	};

	using DS_STATE = DEPTH_STENCIL_STATE;
}
