#pragma once

#include "grng_shader.h"


class grng_frag_shader : public GRNG_SHADER
{
private:
	ID3D11PixelShader			*shader = NULL;


	void						remove_frag_shader_memory();
	void						remove_shader_memory();
	void						set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);

	void						copy_assign(const grng_frag_shader &s);

public:
	grng_frag_shader			&operator=(const grng_frag_shader &s);
	grng_frag_shader(const grng_frag_shader &s);
	grng_frag_shader();
	grng_frag_shader(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);
	~grng_frag_shader();

	void						set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) override;

	static GRNG_BINDABLE		*create_manager_ptr();

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
