
#include "grng_vert_shader.h"


void				grng_vert_shader::remove_vert_shader_memory()
{
	if (this->shader)
	{
		ULONG ref_count = this->shader->Release();
		if (ref_count == 0)
			this->shader = NULL;
	}
}

void				grng_vert_shader::remove_shader_memory()
{
	this->remove_vert_shader_memory();
	grng_shader::remove_shader_memory();
}

void				grng_vert_shader::set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines)
{
	grng_shader::set_shader_memory(shader_file, entry, GRNG_VERT_SHADER_TARGET, defines);
	HRESULT hr = this->device->CreateVertexShader(this->shader_blob->GetBufferPointer(), this->shader_blob->GetBufferSize(), NULL, &this->shader);
}

void				grng_vert_shader::set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines)
{
	this->remove_shader_memory();
	this->set_shader_memory(shader_file, entry, defines);
}

GRNG_BINDABLE		*grng_vert_shader::create_ptr()
{
	grng_vert_shader *vs = new grng_vert_shader;

	return (vs);
}
