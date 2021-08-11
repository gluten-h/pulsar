
#include "grng_frag_shader.h"


void				grng_frag_shader::remove_frag_shader_memory()
{
	if (this->shader)
	{
		ULONG ref_count = this->shader->Release();
		if (ref_count == 0)
			this->shader = NULL;
	}
}

void				grng_frag_shader::remove_shader_memory()
{
	this->remove_frag_shader_memory();
	grng_shader::remove_shader_memory();
}

void				grng_frag_shader::set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines)
{
	HRESULT hr;

	grng_shader::set_shader_memory(shader_file, entry, GRNG_FRAG_SHADER_TARGET, defines);
	GRNG_GFX_ASSERT(this->device->CreatePixelShader(this->shader_blob->GetBufferPointer(), this->shader_blob->GetBufferSize(), NULL, &this->shader));
}

void				grng_frag_shader::set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines)
{
	this->remove_shader_memory();
	this->set_shader_memory(shader_file, entry, defines);
}


grng_frag_shader	*grng_frag_shader::create()
{
	grng_frag_shader *fs = new grng_frag_shader;
	fs->id = GRNG_BM.add(fs);
	if (fs->id == -1)
	{
		delete fs;
		return (NULL);
	}
	fs->is_alloc = true;

	return (fs);
}
