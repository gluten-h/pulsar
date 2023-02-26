
#include "shader.h"
#include "filesystem/filesystem.h"
#include "exceptions/gfx_exception.h"
#include "utils/shader_include.h"


pulsar::shader::~shader()
{
	this->destroy_shader_blob();
}

void	pulsar::shader::create_shader_blob(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target)
{
	pulsar::shader_include shader_inc;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	GFX_ASSERT(D3DCompileFromFile(pulsar::filesystem::absolute_path(shader_file).c_str(), NULL, &shader_inc, entry, target, flags, 0u, &this->mp_blob, NULL));
}

void	pulsar::shader::destroy_shader_blob()
{
	if (this->mp_blob)
	{
		this->mp_blob->Release();
		this->mp_blob = NULL;
	}
}

ID3DBlob	*pulsar::shader::blob()
{
	return (this->mp_blob);
}
