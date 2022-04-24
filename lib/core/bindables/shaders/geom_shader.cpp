
#include "geom_shader.h"


PULSAR::geom_shader::geom_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_shader(shader_file, entry);
}

PULSAR::geom_shader::~geom_shader()
{
	this->free();
}

void	PULSAR::geom_shader::bind() const
{
	PULSAR::gfx::get().device_context()->GSSetShader(this->mp_shader, NULL, 0u);
}

void	PULSAR::geom_shader::unbind() const
{
	PULSAR::gfx::get().device_context()->GSSetShader(NULL, NULL, 0u);
}
