
#include "vert_shader.h"


void		PULSAR::VERT_SHADER::remove_vert_shader_memory()
{
	if (this->shader)
	{
		ULONG ref_count = this->shader->Release();
		if (ref_count == 0)
			this->shader = NULL;
	}
}

void		PULSAR::VERT_SHADER::remove_shader_memory()
{
	this->remove_vert_shader_memory();
	PULSAR::SHADER::remove_shader_memory();
}

void		PULSAR::VERT_SHADER::set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines)
{
	HRESULT hr;

	PULSAR::SHADER::set_shader_memory(shader_file, entry, VERT_SHADER_TARGET, defines);
	GFX_ASSERT(this->device->CreateVertexShader(this->shader_blob->GetBufferPointer(), this->shader_blob->GetBufferSize(), NULL, &this->shader));
}

void		PULSAR::VERT_SHADER::set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines)
{
	this->remove_shader_memory();
	this->set_shader_memory(shader_file, entry, defines);
}


PULSAR::VERT_SHADER		*PULSAR::VERT_SHADER::create()
{
	return ((PULSAR::VERT_SHADER*)PULSAR::BINDABLE::add_to_manager(new PULSAR::VERT_SHADER));
}
