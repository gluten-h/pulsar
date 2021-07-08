#pragma once

#include "grng_shader.h"


class grng_vert_shader : public GRNG_SHADER
{
private:
	ID3D11VertexShader			*shader = NULL;

	void						remove_vert_shader_memory();
	void						remove_shader_memory();
	void						set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);

	void						copy_assign(const grng_vert_shader &s);

public:
	grng_vert_shader			&operator=(const grng_vert_shader &s);
	grng_vert_shader(const grng_vert_shader &s);
	grng_vert_shader();
	grng_vert_shader(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);
	~grng_vert_shader();


	void						set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) override;

	static GRNG_BINDABLE		*create_ptr();

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
