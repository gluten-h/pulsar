
#include "frag_shader.h"


void		PULSAR::FRAG_SHADER::copy_assign(const FRAG_SHADER &s)
{
	this->shader_blob = s.shader_blob;
	this->shader = s.shader;
	if (this->shader_blob)
		this->shader_blob->AddRef();
	if (this->shader)
		this->shader->AddRef();
}


PULSAR::FRAG_SHADER		&PULSAR::FRAG_SHADER::operator=(const FRAG_SHADER &s)
{
	if (this->shader_blob != s.shader_blob)
		PULSAR::SHADER::remove_shader_memory();
	if (this->shader != s.shader)
		this->remove_frag_shader_memory();

	this->copy_assign(s);

	return (*this);
}

PULSAR::FRAG_SHADER::FRAG_SHADER(const FRAG_SHADER &s) : PULSAR::SHADER()
{
	this->type = PULSAR::BINDABLE_TYPE::FRAG_SHADER;
	this->copy_assign(s);
}

PULSAR::FRAG_SHADER::FRAG_SHADER() : PULSAR::SHADER()
{
	this->type = PULSAR::BINDABLE_TYPE::FRAG_SHADER;
}

PULSAR::FRAG_SHADER::FRAG_SHADER(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) : PULSAR::SHADER()
{
	this->type = PULSAR::BINDABLE_TYPE::FRAG_SHADER;
	this->set_shader_memory(shader_file, entry, defines);
}

PULSAR::FRAG_SHADER::~FRAG_SHADER()
{
	this->remove_shader_memory();
}
