
#include "input_layout.h"


PULSAR::input_layout::input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements)
{
	this->create_input_layout(shader_blob, ied, ied_num_elements);
}

PULSAR::input_layout::~input_layout()
{
	this->free();
}

void	PULSAR::input_layout::bind() const
{
	PULSAR::gfx::get().device_context()->IASetInputLayout(this->mp_layout);
}

void	PULSAR::input_layout::unbind() const
{
	PULSAR::gfx::get().device_context()->IASetInputLayout(NULL);
}
