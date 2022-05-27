
#include "input_layout.h"


pulsar::input_layout::input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements)
{
	this->create_input_layout(shader_blob, ied, ied_num_elements);
}

pulsar::input_layout::~input_layout()
{
	this->free();
}

void	pulsar::input_layout::bind() const
{
	pulsar::gfx::instance().device_context()->IASetInputLayout(this->mp_layout);
}

void	pulsar::input_layout::unbind() const
{
	pulsar::gfx::instance().device_context()->IASetInputLayout(NULL);
}
