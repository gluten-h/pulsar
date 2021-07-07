#pragma once

#include "grng_shader.h"


class grng_vert_shader : public GRNG_SHADER
{
private:
	ID3D11VertexShader		*shader = NULL;

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
		grng_shader::set_shader_memory(shader_file, entry, GRNG_VERT_SHADER_TARGET, defines);
		HRESULT hr = this->device->CreateVertexShader(this->shader_blob->GetBufferPointer(), this->shader_blob->GetBufferSize(), NULL, &this->shader);
	}

public:
	grng_vert_shader() : GRNG_SHADER()
	{
		this->type = GRNG_BINDABLE_TYPE::VERT_SHADER;
	}
	grng_vert_shader(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) : GRNG_SHADER()
	{
		this->type = GRNG_BINDABLE_TYPE::VERT_SHADER;

		this->set_shader_memory(shader_file, entry, defines);
	}

	~grng_vert_shader()
	{
		this->remove_shader_memory();
	}


	void		set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) override
	{
		this->remove_shader_memory();
		this->set_shader_memory(shader_file, entry, defines);
	}


	static GRNG_BINDABLE		*create_ptr()
	{
		grng_vert_shader *vs = new grng_vert_shader;

		return (vs);
	}


	void		bind() override
	{
		this->device_context->VSSetShader(this->shader, NULL, 0u);
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

using GRNG_VERT_SHADER = grng_vert_shader;
