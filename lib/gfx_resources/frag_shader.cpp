
#include "frag_shader.h"
#include "exceptions/gfx_exception.h"


pulsar::frag_shader::frag_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_frag_shader(shader_file, entry);
}

pulsar::frag_shader::~frag_shader()
{
	this->destroy_frag_shader();
}

void	pulsar::frag_shader::create_frag_shader(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->create_shader_blob(shader_file, entry, pulsar::FRAG_TARGET);
	GFX_ASSERT(pulsar::gfx::instance().device()->CreatePixelShader(this->blob()->GetBufferPointer(), this->blob()->GetBufferSize(), NULL, &this->mp_shader));
}

void	pulsar::frag_shader::destroy_frag_shader()
{
	if (this->mp_shader)
	{
		this->mp_shader->Release();
		this->mp_shader = NULL;
	}
}

void	pulsar::frag_shader::set(const LPCWSTR shader_file, const LPCSTR entry)
{
	this->destroy_shader_blob();
	this->destroy_frag_shader();
	this->create_frag_shader(shader_file, entry);
}

ID3D11PixelShader	*pulsar::frag_shader::shader()
{
	return (this->mp_shader);
}

void	pulsar::frag_shader::bind() const
{
	pulsar::gfx::instance().device_context()->PSSetShader(this->mp_shader, NULL, 0u);
}

void	pulsar::frag_shader::unbind() const
{
	pulsar::gfx::instance().device_context()->PSSetShader(NULL, NULL, 0u);
}
