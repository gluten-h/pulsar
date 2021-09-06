
#include "geom_shader.h"


void		PULSAR::GEOM_SHADER::copy_assign(const GEOM_SHADER &s)
{
	this->shader_blob = s.shader_blob;
	this->shader = s.shader;
	if (this->shader_blob)
		this->shader_blob->AddRef();
	if (this->shader)
		this->shader->AddRef();
}


PULSAR::GEOM_SHADER		&PULSAR::GEOM_SHADER::operator=(const GEOM_SHADER &s)
{
	if (this->shader_blob != s.shader_blob)
		PULSAR::SHADER::remove_shader_memory();
	if (this->shader != s.shader)
		this->remove_geom_shader_memory();

	this->copy_assign(s);

	return (*this);
}

PULSAR::GEOM_SHADER::GEOM_SHADER(const GEOM_SHADER &s) : PULSAR::SHADER()
{
	this->type = PULSAR::BINDABLE_TYPE::GEOM_SHADER;
	this->copy_assign(s);
}

PULSAR::GEOM_SHADER::GEOM_SHADER() : PULSAR::SHADER()
{
	this->type = PULSAR::BINDABLE_TYPE::GEOM_SHADER;
}

PULSAR::GEOM_SHADER::GEOM_SHADER(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) : PULSAR::SHADER()
{
	this->type = PULSAR::BINDABLE_TYPE::GEOM_SHADER;
	this->set_shader_memory(shader_file, entry, defines);
}

PULSAR::GEOM_SHADER::~GEOM_SHADER()
{
	this->remove_shader_memory();
}
