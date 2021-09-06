
#include "input_layout.h"


void	PULSAR::INPUT_LAYOUT::copy_assign(const INPUT_LAYOUT &il)
{
	this->input_layout = il.input_layout;
	if (this->input_layout)
		this->input_layout->AddRef();
}


PULSAR::INPUT_LAYOUT		&PULSAR::INPUT_LAYOUT::operator=(const INPUT_LAYOUT &il)
{
	if (this->input_layout != il.input_layout)
		this->remove_input_layout();
	this->copy_assign(il);

	return (*this);
}

PULSAR::INPUT_LAYOUT::INPUT_LAYOUT(const INPUT_LAYOUT &il) : PULSAR::BINDABLE()
{
	this->type = BINDABLE_TYPE::INPUT_LAYOUT;
	this->copy_assign(il);
}

PULSAR::INPUT_LAYOUT::INPUT_LAYOUT() : PULSAR::BINDABLE()
{
	this->type = BINDABLE_TYPE::INPUT_LAYOUT;
}

PULSAR::INPUT_LAYOUT::INPUT_LAYOUT(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements) : PULSAR::BINDABLE()
{
	this->type = BINDABLE_TYPE::INPUT_LAYOUT;
	this->set_input_layout_memory(shader_blob, ied, ied_num_elements);
}

PULSAR::INPUT_LAYOUT::~INPUT_LAYOUT()
{
	this->remove_input_layout();
}
