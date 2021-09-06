
#include "input_layout.h"


void	PULSAR::INPUT_LAYOUT::remove_input_layout()
{
	if (this->input_layout)
	{
		ULONG ref_count = this->input_layout->Release();
		if (ref_count == 0)
			this->input_layout = NULL;
	}
}

void	PULSAR::INPUT_LAYOUT::set_input_layout_memory(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements)
{
	HRESULT hr;

	GFX_ASSERT(this->device->CreateInputLayout(ied, ied_num_elements, shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), &this->input_layout));
}

void	PULSAR::INPUT_LAYOUT::set(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements)
{
	this->remove_input_layout();
	this->set_input_layout_memory(shader_blob, ied, ied_num_elements);
}

PULSAR::INPUT_LAYOUT	*PULSAR::INPUT_LAYOUT::create()
{
	return ((PULSAR::INPUT_LAYOUT*)PULSAR::BINDABLE::add_to_manager(new PULSAR::INPUT_LAYOUT));
}
