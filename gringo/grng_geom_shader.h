#pragma once

#include "grng_shader.h"


class grng_geom_shader : public GRNG_SHADER
{
private:
	ID3D11GeometryShader	*shader = NULL;

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
		grng_shader::set_shader_memory(shader_file, entry, GRNG_GEOM_SHADER_TARGET, defines);
		HRESULT hr = this->device->CreateGeometryShader(this->shader_blob->GetBufferPointer(), this->shader_blob->GetBufferSize(), NULL, &this->shader);
	}

public:
	grng_geom_shader() : GRNG_SHADER()
	{
		this->type = GRNG_BINDABLE_TYPE::GEOM_SHADER;
	}
	grng_geom_shader(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) : GRNG_SHADER()
	{
		this->type = GRNG_BINDABLE_TYPE::GEOM_SHADER;

		this->set_shader_memory(shader_file, entry, defines);
	}

	~grng_geom_shader()
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
		grng_geom_shader *gs = new grng_geom_shader;

		return (gs);
	}


	void		bind() override
	{
		this->device_context->GSSetShader(this->shader, NULL, 0u);
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

using GRNG_GEOM_SHADER = grng_geom_shader;
