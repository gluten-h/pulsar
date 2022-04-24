
#include "vert_shader.h"




PULSAR::vert_shader::vert_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_shader(shader_file, entry);
}

PULSAR::vert_shader::~vert_shader()
{
	this->free();
}

void	PULSAR::vert_shader::bind() const
{
	PULSAR::gfx::get().device_context()->VSSetShader(this->mp_shader, NULL, 0u);
}

void	PULSAR::vert_shader::unbind() const
{
	PULSAR::gfx::get().device_context()->VSSetShader(NULL, NULL, 0u);
}
