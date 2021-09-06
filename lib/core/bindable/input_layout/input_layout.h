#pragma once

#include "bindable.h"
#include "bindable_entity.h"


namespace PULSAR
{
	class INPUT_LAYOUT : public BINDABLE
	{
	private:
		ID3D11InputLayout	*input_layout = NULL;


		void	remove_input_layout();
		void	set_input_layout_memory(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);

		void	copy_assign(const INPUT_LAYOUT &il);

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
		INPUT_LAYOUT	&operator=(const INPUT_LAYOUT &il);
		INPUT_LAYOUT(const INPUT_LAYOUT &il);
		INPUT_LAYOUT();
		INPUT_LAYOUT(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);
		~INPUT_LAYOUT();

		void	set(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);

		static INPUT_LAYOUT		*create();

		void	bind() const override
		{
			this->device_context->IASetInputLayout(this->input_layout);
			BINDABLE::add_unbind(*this);
		}

		void	unbind() const override
		{
			this->device_context->IASetInputLayout(NULL);
		}
	};
}
