
#include "vert_shader.h"


void	PULSAR::vert_shader::free()
{
	if (this->mp_shader)
	{
		this->mp_shader->Release();
		this->mp_shader = NULL;
	}
	PULSAR::shader::free();
}

void	PULSAR::vert_shader::create_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	PULSAR::shader::create_shader(shader_file, entry, VERT_TARGET);
	GFX_ASSERT(PULSAR::gfx::get().device()->CreateVertexShader(this->mp_shader_blob->GetBufferPointer(), this->mp_shader_blob->GetBufferSize(), NULL, &this->mp_shader));
}

void	PULSAR::vert_shader::set(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->free();
	this->create_shader(shader_file, entry);
}

const ID3D11VertexShader	*PULSAR::vert_shader::get() const
{
	return (this->mp_shader);
}
