
#include "frag_shader.h"


pulsar::frag_shader::frag_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_shader(shader_file, entry);
}

pulsar::frag_shader::~frag_shader()
{
	this->free();
}

void	pulsar::frag_shader::bind() const
{
	pulsar::gfx::instance().device_context()->PSSetShader(this->mp_shader, NULL, 0u);
}

void	pulsar::frag_shader::unbind() const
{
	pulsar::gfx::instance().device_context()->PSSetShader(NULL, NULL, 0u);
}
