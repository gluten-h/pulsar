
#include "geom_shader.h"
#include "exceptions/gfx_exception.h"


pulsar::geom_shader::geom_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_geom_shader(shader_file, entry);
}

pulsar::geom_shader::~geom_shader()
{
	this->destroy_geom_shader();
}

void	pulsar::geom_shader::create_geom_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_shader_blob(shader_file, entry, pulsar::GEOM_TARGET);
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateGeometryShader(this->blob()->GetBufferPointer(), this->blob()->GetBufferSize(), NULL, &this->mp_shader));
}

void	pulsar::geom_shader::destroy_geom_shader()
{
	if (this->mp_shader)
	{
		this->mp_shader->Release();
		this->mp_shader = NULL;
	}
}

void	pulsar::geom_shader::set(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->destroy_shader_blob();
	this->destroy_geom_shader();
	this->create_geom_shader(shader_file, entry);
}

ID3D11GeometryShader	*pulsar::geom_shader::shader()
{
	return (this->mp_shader);
}

void	pulsar::geom_shader::bind() const
{
	pulsar::gfx::instance().device_context()->GSSetShader(this->mp_shader, NULL, 0u);
}

void	pulsar::geom_shader::unbind() const
{
	pulsar::gfx::instance().device_context()->GSSetShader(NULL, NULL, 0u);
}
