
#include "vert_shader.h"


void		PULSAR::VERT_SHADER::copy_assign(const VERT_SHADER &s)
{
	this->shader_blob = s.shader_blob;
	this->shader = s.shader;
	if (this->shader_blob)
		this->shader_blob->AddRef();
	if (this->shader)
		this->shader->AddRef();
}


PULSAR::VERT_SHADER		&PULSAR::VERT_SHADER::operator=(const VERT_SHADER &s)
{
	if (this->shader_blob != s.shader_blob)
		PULSAR::SHADER::remove_shader_memory();
	if (this->shader != s.shader)
		this->remove_vert_shader_memory();

	this->copy_assign(s);

	return (*this);
}

PULSAR::VERT_SHADER::VERT_SHADER(const VERT_SHADER &s) : PULSAR::SHADER()
{
	this->type = PULSAR::BINDABLE_TYPE::VERT_SHADER;
	this->copy_assign(s);
}

PULSAR::VERT_SHADER::VERT_SHADER() : PULSAR::SHADER()
{
	this->type = PULSAR::BINDABLE_TYPE::VERT_SHADER;
}

PULSAR::VERT_SHADER::VERT_SHADER(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) : PULSAR::SHADER()
{
	this->type = PULSAR::BINDABLE_TYPE::VERT_SHADER;
	this->set_shader_memory(shader_file, entry, defines);
}

PULSAR::VERT_SHADER::~VERT_SHADER()
{
	this->remove_shader_memory();
}
