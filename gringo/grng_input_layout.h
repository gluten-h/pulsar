#pragma once

#include "grng_bindable.h"


class grng_input_layout : public GRNG_BINDABLE
{
private:
	ID3D11InputLayout	*input_layout = NULL;


	void	remove_input_layout()
	{
		if (this->input_layout)
		{
			this->input_layout->Release();
			this->input_layout = NULL;
		}
	}

	void	set_input_layout_memory(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements)
	{
		HRESULT hr = this->device->CreateInputLayout(ied, ied_num_elements, shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), &this->input_layout);
	}

public:
	grng_input_layout() = delete;
	grng_input_layout(const grng_input_layout& il) = delete;
	grng_input_layout(grng_input_layout &&il) = delete;
	grng_input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements) : GRNG_BINDABLE()
	{
		this->set_input_layout_memory(shader_blob, ied, ied_num_elements);
	}

	void	set_input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements)
	{
		this->remove_input_layout();
		this->set_input_layout_memory(shader_blob, ied, ied_num_elements);
	}

	void	bind() override
	{
		this->device_context->IASetInputLayout(this->input_layout);
	}
};

using GRNG_INPUT_LAYOUT = grng_input_layout;
