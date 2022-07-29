
#include "input_layout.h"
#include "exceptions/gfx_exception.h"


pulsar::input_layout::input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT num_elements)
{
	this->create_input_layout(shader_blob, ied, num_elements);
}

pulsar::input_layout::~input_layout()
{
	this->destroy_input_layout();
}

void	pulsar::input_layout::create_input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT num_elements)
{
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateInputLayout(ied, num_elements, shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), &this->mp_layout));
}

void	pulsar::input_layout::destroy_input_layout()
{
	if (this->mp_layout)
	{
		this->mp_layout->Release();
		this->mp_layout = NULL;
	}
}

void	pulsar::input_layout::set(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT num_elements)
{
	this->destroy_input_layout();
	this->create_input_layout(shader_blob, ied, num_elements);
}

void	pulsar::input_layout::bind() const
{
	pulsar::gfx::instance().device_context()->IASetInputLayout(this->mp_layout);
}

void	pulsar::input_layout::unbind() const
{
	pulsar::gfx::instance().device_context()->IASetInputLayout(NULL);
}
