
#include "geom_shader.h"


pulsar::geom_shader::geom_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_shader(shader_file, entry);
}

pulsar::geom_shader::~geom_shader()
{
	this->free();
}

void	pulsar::geom_shader::bind() const
{
	pulsar::gfx::instance().device_context()->GSSetShader(this->mp_shader, NULL, 0u);
}

void	pulsar::geom_shader::unbind() const
{
	pulsar::gfx::instance().device_context()->GSSetShader(NULL, NULL, 0u);
}
