
#include "vert_shader.h"
#include "exceptions/gfx_exception.h"


pulsar::vert_shader::vert_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_vert_shader(shader_file, entry);
}

pulsar::vert_shader::~vert_shader()
{
	this->destroy_vert_shader();
}

void	pulsar::vert_shader::create_vert_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_shader_blob(shader_file, entry, pulsar::VERT_TARGET);
	GFX_ASSERT(pulsar::gfx::instance().device()->CreateVertexShader(this->blob()->GetBufferPointer(), this->blob()->GetBufferSize(), NULL, &this->mp_shader));
}

void	pulsar::vert_shader::destroy_vert_shader()
{
	if (this->mp_shader)
	{
		this->mp_shader->Release();
		this->mp_shader = NULL;
	}
}

void	pulsar::vert_shader::set(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->destroy_shader_blob();
	this->destroy_vert_shader();
	this->create_vert_shader(shader_file, entry);
}

ID3D11VertexShader	*pulsar::vert_shader::shader()
{
	return (this->mp_shader);
}

void	pulsar::vert_shader::bind() const
{
	pulsar::gfx::instance().device_context()->VSSetShader(this->mp_shader, NULL, 0u);
}

void	pulsar::vert_shader::unbind() const
{
	pulsar::gfx::instance().device_context()->VSSetShader(NULL, NULL, 0u);
}
