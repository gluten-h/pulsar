#pragma once

#include "grng_shader.h"


class grng_frag_shader : public GRNG_SHADER
{
private:
	ID3D11PixelShader		*shader = NULL;

	void		remove_shader_memory()
	{
		if (this->shader)
		{
			this->shader->Release();
			this->shader = NULL;
		}
		grng_shader::remove_shader_memory();
	}

	void		set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry)
	{
		grng_shader::set_shader_memory(shader_file, entry, GRNG_FRAG_SHADER_TARGET);
		HRESULT hr = this->device->CreatePixelShader(this->shader_blob->GetBufferPointer(), this->shader_blob->GetBufferSize(), NULL, &this->shader);
	}

public:
	grng_frag_shader() = delete;
	grng_frag_shader(const grng_frag_shader &fs) = delete;
	grng_frag_shader(grng_frag_shader &&fs) = delete;
	grng_frag_shader(const LPCWSTR shader_file, const LPCSTR entry) : GRNG_SHADER(shader_file, entry, GRNG_FRAG_SHADER_TARGET)
	{
		this->type = GRNG_SHADER_TYPE::GRNG_FRAG_SHADER;
		this->set_shader_memory(shader_file, entry);
	}

	~grng_frag_shader()
	{
		this->remove_shader_memory();
	}


	void		set_shader(const LPCWSTR shader_file, const LPCSTR entry) override
	{
		this->remove_shader_memory();
		this->set_shader_memory(shader_file, entry);
	}

	void		bind() override
	{
		this->device_context->PSSetShader(this->shader, NULL, 0u);
	}

	const void	*get_shader() const
	{
		return ((void*)this->shader);
	}
};

using GRNG_FRAG_SHADER = grng_frag_shader;
