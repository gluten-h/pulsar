
#include "vert_shader.h"
#include "exceptions/gfx_exception.h"


void	pulsar::vert_shader::free()
{
	if (this->mp_shader)
	{
		this->mp_shader->Release();
		this->mp_shader = NULL;
	}
	pulsar::shader::free();
}

void	pulsar::vert_shader::create_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	pulsar::shader::create_shader(shader_file, entry, VERT_TARGET);
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateVertexShader(this->mp_shader_blob->GetBufferPointer(), this->mp_shader_blob->GetBufferSize(), NULL, &this->mp_shader));
}

void	pulsar::vert_shader::set(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->free();
	this->create_shader(shader_file, entry);
}

const ID3D11VertexShader	*pulsar::vert_shader::get() const
{
	return (this->mp_shader);
}
