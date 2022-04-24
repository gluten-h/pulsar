
#include "shader.h"
#include "filesystem/filesystem.h"
#include "exceptions/macro/gfx_exc_macros.h"
#include "shader_include.h"


void	PULSAR::shader::free()
{
	if (this->mp_shader_blob)
	{
		this->mp_shader_blob->Release();
		this->mp_shader_blob = NULL;
	}
}

PULSAR::shader::~shader()
{
	this->free();
}

void	PULSAR::shader::create_shader(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target)
{
	PULSAR::shader_include shader_inc;
	GFX_ASSERT(D3DCompileFromFile(PULSAR::filesystem::absolute_path(shader_file).c_str(), NULL, &shader_inc, entry, target, NULL, NULL, &this->mp_shader_blob, NULL));
}

ID3DBlob	*PULSAR::shader::get_shader_blob() const
{
	return (this->mp_shader_blob);
}
