#pragma once

#include "bindable/bindable.h"


namespace PULSAR
{
	class input_layout : public PULSAR::bindable
	{
	private:
		ID3D11InputLayout	*mp_layout = NULL;

	private:
		void	create_input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);
		void	free();

	public:
		input_layout &operator=(const input_layout&) = delete;
		input_layout &operator=(input_layout&&) = delete;
		input_layout(const input_layout&) = delete;
		input_layout(input_layout&&) = delete;
		input_layout() = default;
		input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);
		~input_layout();

		void	set(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements);

		void	bind() const override;
		void	unbind() const override;
	};
}
