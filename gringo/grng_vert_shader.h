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

	void		set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry)
	{
		grng_shader::set_shader_memory(shader_file, entry, GRNG_VERT_SHADER_TARGET);
		HRESULT hr = this->device->CreateVertexShader(this->shader_blob->GetBufferPointer(), this->shader_blob->GetBufferSize(), NULL, &this->shader);
	}

public:
	grng_vert_shader() = delete;
	grng_vert_shader(const grng_vert_shader &vs) = delete;
	grng_vert_shader(grng_vert_shader &&vs) = delete;
	grng_vert_shader(const LPCWSTR shader_file, const LPCSTR entry) : GRNG_SHADER(shader_file, entry, GRNG_VERT_SHADER_TARGET)
	{
		this->type = GRNG_SHADER_TYPE::GRNG_VERT_SHADER;
		this->set_shader_memory(shader_file, entry);
	}

	~grng_vert_shader()
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
		this->device_context->VSSetShader(this->shader, NULL, 0u);
	}

	const void	*get_shader() const
	{
		return ((void*)this->shader);
	}
};

using GRNG_VERT_SHADER = grng_vert_shader;
