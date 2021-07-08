
#include "grng_shader.h"


void			grng_shader::remove_shader_memory()
{
	if (shader_blob)
	{
		ULONG ref_count = this->shader_blob->Release();
		if (ref_count == 0)
			this->shader_blob = NULL;
	}
}

void			grng_shader::set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target, const D3D_SHADER_MACRO *defines)
{
	ID3DBlob *err_msg;
	GRNG_SHADER_INCLUDE s_inc;
	HRESULT hr = D3DCompileFromFile(shader_file, defines, &s_inc, entry, target, NULL, NULL, &this->shader_blob, &err_msg);
	if (hr != S_OK)
	{
		std::ofstream os("resources/log.txt");
		os.clear();

		const char *error = static_cast<const char*>(err_msg->GetBufferPointer());
		os << error << '\n';

		os.close();
		exit(0);
	}
}
