
#include "grng_vert_shader.h"


void					grng_vert_shader::copy_assign(const grng_vert_shader &s)
{
	this->shader_blob = s.shader_blob;
	this->shader = s.shader;
	if (this->shader_blob)
		this->shader_blob->AddRef();
	if (this->shader)
		this->shader->AddRef();
}


grng_vert_shader		&grng_vert_shader::operator=(const grng_vert_shader &s)
{
	if (this->shader_blob != s.shader_blob)
		grng_shader::remove_shader_memory();
	if (this->shader != s.shader)
		this->remove_vert_shader_memory();

	this->copy_assign(s);

	return (*this);
}

grng_vert_shader::grng_vert_shader(const grng_vert_shader &s) : GRNG_SHADER()
{
	this->copy_assign(s);
}

grng_vert_shader::grng_vert_shader() : GRNG_SHADER()
{
	this->type = GRNG_BINDABLE_TYPE::VERT_SHADER;
}

grng_vert_shader::grng_vert_shader(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) : GRNG_SHADER()
{
	this->type = GRNG_BINDABLE_TYPE::VERT_SHADER;
	this->set_shader_memory(shader_file, entry, defines);
}

grng_vert_shader::~grng_vert_shader()
{
	this->remove_shader_memory();
}
