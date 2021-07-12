
#include "grng_frag_shader.h"


void					grng_frag_shader::copy_assign(const grng_frag_shader &s)
{
	this->shader_blob = s.shader_blob;
	this->shader = s.shader;
	if (this->shader_blob)
		this->shader_blob->AddRef();
	if (this->shader)
		this->shader->AddRef();
}


grng_frag_shader		&grng_frag_shader::operator=(const grng_frag_shader &s)
{
	if (this->shader_blob != s.shader_blob)
		grng_shader::remove_shader_memory();
	if (this->shader != s.shader)
		this->remove_frag_shader_memory();

	this->copy_assign(s);

	return (*this);
}

grng_frag_shader::grng_frag_shader(const grng_frag_shader &s) : GRNG_SHADER()
{
	this->type = GRNG_BINDABLE_TYPE::FRAG_SHADER;
	this->copy_assign(s);
}

grng_frag_shader::grng_frag_shader() : GRNG_SHADER()
{
	this->type = GRNG_BINDABLE_TYPE::FRAG_SHADER;
}

grng_frag_shader::grng_frag_shader(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) : GRNG_SHADER()
{
	this->type = GRNG_BINDABLE_TYPE::FRAG_SHADER;

	this->set_shader_memory(shader_file, entry, defines);
}

grng_frag_shader::~grng_frag_shader()
{
	this->remove_shader_memory();
}
