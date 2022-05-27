
#include "vert_shader.h"




pulsar::vert_shader::vert_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_shader(shader_file, entry);
}

pulsar::vert_shader::~vert_shader()
{
	this->free();
}

void	pulsar::vert_shader::bind() const
{
	pulsar::gfx::instance().device_context()->VSSetShader(this->mp_shader, NULL, 0u);
}

void	pulsar::vert_shader::unbind() const
{
	pulsar::gfx::instance().device_context()->VSSetShader(NULL, NULL, 0u);
}
