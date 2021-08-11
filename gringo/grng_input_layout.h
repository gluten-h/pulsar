#pragma once

#include "grng_bindable.h"
#include "grng_bindable_entity.h"


class grng_input_layout : public GRNG_BINDABLE
{
private:
	ID3D11InputLayout	*input_layout = NULL;


	void					remove_input_layout();
	void					set_input_layout_memory(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);

	void					copy_assign(const grng_input_layout &il);

protected:
	void		remove_from_entities() override
	{
		for (auto &it : this->entities)
			it->_remove_bindable_ignore_entity(this);
		this->entities.clear();
	}

public:
	using GRNG_BINDABLE::bind;

public:
	grng_input_layout		&operator=(const grng_input_layout &il);
	grng_input_layout(const grng_input_layout &il);
	grng_input_layout();
	grng_input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);
	~grng_input_layout();

	void					set(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);

	static grng_input_layout	*create();

	void		bind() const override
	{
		this->device_context->IASetInputLayout(this->input_layout);
		GRNG_BINDABLE::add_unbind(*this);
	}

	void		unbind() const override
	{
		this->device_context->IASetInputLayout(NULL);
	}
};

using GRNG_INPUT_LAYOUT = grng_input_layout;
