
#include "frag_shader.h"


PULSAR::frag_shader::frag_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_shader(shader_file, entry);
}

PULSAR::frag_shader::~frag_shader()
{
	this->free();
}

void	PULSAR::frag_shader::bind() const
{
	PULSAR::gfx::get().device_context()->PSSetShader(this->mp_shader, NULL, 0u);
}

void	PULSAR::frag_shader::unbind() const
{
	PULSAR::gfx::get().device_context()->PSSetShader(NULL, NULL, 0u);
}
