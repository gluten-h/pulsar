
#include "grng_shader_manager.h"


void	grng_sm::create_vert_shader(ID3DBlob *shader_blob, GRNG_SHADER *&shader_ptr)
{
	HRESULT hr;

	shader_ptr->type = GRNG_SHADER_TYPE::GRNG_VERT_SHADER;

	ID3D11VertexShader *vs;
	hr = grng_sm::device->CreateVertexShader(shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), NULL, &vs);
	shader_ptr->shader = (void*)vs;

	shader_ptr->shader_blob = shader_blob;
}

void	grng_sm::create_geom_shader(ID3DBlob *shader_blob, GRNG_SHADER *&shader_ptr)
{
	HRESULT hr;

	shader_ptr->type = GRNG_SHADER_TYPE::GRNG_GEOM_SHADER;
	ID3D11GeometryShader *gs;
	hr = grng_sm::device->CreateGeometryShader(shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), NULL, &gs);
	shader_ptr->shader = (void*)gs;

	shader_ptr->shader_blob = shader_blob;
}

void	grng_sm::create_frag_shader(ID3DBlob *shader_blob, GRNG_SHADER *&shader_ptr)
{
	HRESULT hr;

	shader_ptr->type = GRNG_SHADER_TYPE::GRNG_FRAG_SHADER;
	ID3D11PixelShader *fs;
	hr = grng_sm::device->CreatePixelShader(shader_blob->GetBufferPointer(), shader_blob->GetBufferSize(), NULL, &fs);
	shader_ptr->shader = (void*)fs;

	shader_ptr->shader_blob = shader_blob;
}


HRESULT		grng_sm::create_vert_shader_layout_secure(unsigned int id, D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get_secure(id);
	if (!shader_ptr || shader_ptr->type != GRNG_SHADER_TYPE::GRNG_VERT_SHADER || !ied)
		return S_FALSE;

	ID3D11InputLayout *layout;
	HRESULT hr = grng_sm::device->CreateInputLayout(ied, ied_num_elements, shader_ptr->shader_blob->GetBufferPointer(), shader_ptr->shader_blob->GetBufferSize(), &layout);
	shader_ptr->layout = layout;

	return (hr);
}

HRESULT		grng_sm::create_vert_shader_layout(unsigned int id, D3D11_INPUT_ELEMENT_DESC *ied, UINT ied_num_elements)
{
	GRNG_SHADER *shader_ptr = grng_sm::shader.get(id);
	ID3D11InputLayout *layout;
	HRESULT hr = grng_sm::device->CreateInputLayout(ied, ied_num_elements, shader_ptr->shader_blob->GetBufferPointer(), shader_ptr->shader_blob->GetBufferSize(), &layout);
	shader_ptr->layout = layout;

	return (hr);
}
