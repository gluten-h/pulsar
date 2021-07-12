
#include "grng_input_layout.h"


void					grng_input_layout::copy_assign(const grng_input_layout &il)
{
	this->input_layout = il.input_layout;
	if (this->input_layout)
		this->input_layout->AddRef();
}


grng_input_layout		&grng_input_layout::operator=(const grng_input_layout &il)
{
	if (this->input_layout != il.input_layout)
		this->remove_input_layout();
	this->copy_assign(il);

	return (*this);
}

grng_input_layout::grng_input_layout(const grng_input_layout &il) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::INPUT_LAYOUT;
	this->copy_assign(il);
}

grng_input_layout::grng_input_layout() : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::INPUT_LAYOUT;
}

grng_input_layout::grng_input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements) : GRNG_BINDABLE()
{
	this->type = GRNG_BINDABLE_TYPE::INPUT_LAYOUT;
	this->set_input_layout_memory(shader_blob, ied, ied_num_elements);
}

grng_input_layout::~grng_input_layout()
{
	this->remove_input_layout();
}
