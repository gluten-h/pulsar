
#include "grng_input_layout.h"


void				grng_input_layout::remove_input_layout()
{
	if (this->input_layout)
	{
		ULONG ref_count = this->input_layout->Release();
		if (ref_count == 0)
			this->input_layout = NULL;
	}
}

void				grng_input_layout::set_input_layout_memory(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements)
{
	HRESULT hr;

	GRNG_GFX_ASSERT(this->device->CreateInputLayout(ied, ied_num_elements, shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), &this->input_layout));
}

void				grng_input_layout::set(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements)
{
	this->remove_input_layout();
	this->set_input_layout_memory(shader_blob, ied, ied_num_elements);
}

grng_input_layout	*grng_input_layout::create()
{
	grng_input_layout *il = new grng_input_layout;
	il->id = GRNG_BM.add(il);
	if (il->id == -1)
	{
		delete il;
		return (NULL);
	}
	il->is_alloc = true;

	return (il);
}
