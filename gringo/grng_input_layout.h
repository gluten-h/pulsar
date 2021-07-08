#pragma once

#include "grng_bindable.h"


class grng_input_layout : public GRNG_BINDABLE
{
private:
	ID3D11InputLayout	*input_layout = NULL;


	void					remove_input_layout();
	void					set_input_layout_memory(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);

	void					copy_assign(const grng_input_layout &il);

public:
	grng_input_layout		&operator=(const grng_input_layout &il);
	grng_input_layout(const grng_input_layout &il);
	grng_input_layout();
	grng_input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);
	~grng_input_layout();

	void					set(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);

	static GRNG_BINDABLE	*create_manager_ptr();

	void		bind() override
	{
		this->device_context->IASetInputLayout(this->input_layout);
	}
};

using GRNG_INPUT_LAYOUT = grng_input_layout;
