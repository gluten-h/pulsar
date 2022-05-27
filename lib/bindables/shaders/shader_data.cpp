
#include "shader.h"
#include "filesystem/filesystem.h"
#include "exceptions/gfx_exception.h"
#include "utils/shader_include.h"


void	pulsar::shader::free()
{
	if (this->mp_shader_blob)
	{
		this->mp_shader_blob->Release();
		this->mp_shader_blob = NULL;
	}
}

pulsar::shader::~shader()
{
	this->free();
}

void	pulsar::shader::create_shader(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target)
{
	pulsar::shader_include shader_inc;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	flags |= D3DCOMPILE_DEBUG;
#endif

	GFX_ASSERT(D3DCompileFromFile(pulsar::filesystem::absolute_path(shader_file).c_str(), NULL, &shader_inc, entry, target, flags, 0u, &this->mp_shader_blob, NULL));
}

ID3DBlob	*pulsar::shader::get_shader_blob() const
{
	return (this->mp_shader_blob);
}
