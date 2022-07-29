#pragma once

#include "gfx/gfx.h"


namespace pulsar
{
	class input_layout
	{
	private:
		ID3D11InputLayout *mp_layout = NULL;

		void	create_input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT num_elements);
		void	destroy_input_layout();

	public:
		input_layout &operator=(const input_layout&) = delete;
		input_layout &operator=(input_layout&&) = delete;
		input_layout(const input_layout&) = delete;
		input_layout(input_layout&&) = delete;
		input_layout() = default;
		input_layout(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT num_elements);
		~input_layout();

		void	set(ID3DBlob *shader_blob, const D3D11_INPUT_ELEMENT_DESC *ied, UINT num_elements);

		void	bind() const;
		void	unbind() const;
	};
}
