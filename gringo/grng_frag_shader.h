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

	void		set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines)
	{
		grng_shader::set_shader_memory(shader_file, entry, GRNG_FRAG_SHADER_TARGET, defines);
		HRESULT hr = this->device->CreatePixelShader(this->shader_blob->GetBufferPointer(), this->shader_blob->GetBufferSize(), NULL, &this->shader);
	}

public:
	grng_frag_shader() : GRNG_SHADER()
	{
		this->type = GRNG_BINDABLE_TYPE::FRAG_SHADER;
	}
	grng_frag_shader(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) : GRNG_SHADER()
	{
		this->type = GRNG_BINDABLE_TYPE::FRAG_SHADER;

		this->set_shader_memory(shader_file, entry, defines);
	}

	~grng_frag_shader()
	{
		this->remove_shader_memory();
	}


	void		set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) override
	{
		this->remove_shader_memory();
		this->set_shader_memory(shader_file, entry, defines);
	}


	static GRNG_BINDABLE		*create_manager_ptr()
	{
		grng_frag_shader *fs = new grng_frag_shader;

		return (fs);
	}


	void		bind() override
	{
		this->device_context->PSSetShader(this->shader, NULL, 0u);
	}

	void		destroy() override
	{
		this->remove_shader_memory();
	}


	const void	*get_shader() const
	{
		return ((void*)this->shader);
	}
};

using GRNG_FRAG_SHADER = grng_frag_shader;
