
#include "geom_shader.h"
#include "exceptions/gfx_exception.h"


void	PULSAR::geom_shader::free()
{
	if (this->mp_shader)
	{
		this->mp_shader->Release();
		this->mp_shader = NULL;
	}
	PULSAR::shader::free();
}

void	PULSAR::geom_shader::create_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	PULSAR::shader::create_shader(shader_file, entry, GEOM_TARGET);
	GFX_ASSERT(PULSAR::gfx::get().device()->CreateGeometryShader(this->mp_shader_blob->GetBufferPointer(), this->mp_shader_blob->GetBufferSize(), NULL, &this->mp_shader));
}

void	PULSAR::geom_shader::set(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->free();
	this->create_shader(shader_file, entry);
}

const ID3D11GeometryShader	*PULSAR::geom_shader::get() const
{
	return (this->mp_shader);
}
