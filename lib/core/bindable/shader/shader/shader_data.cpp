
#include "shader.h"


void		PULSAR::SHADER::remove_shader_memory()
{
	if (shader_blob)
	{
		ULONG ref_count = this->shader_blob->Release();
		if (ref_count == 0)
			this->shader_blob = NULL;
	}
}

void		PULSAR::SHADER::set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target, const D3D_SHADER_MACRO *defines)
{
	//HRESULT hr;
	PULSAR::SHADER_INCLUDE s_inc;

	HRESULT hr = D3DCompileFromFile(PULSAR::filesystem::file_path(shader_file).c_str(), defines, &s_inc, entry, target, NULL, NULL, &this->shader_blob, NULL);

	GFX_ASSERT(hr);
}
