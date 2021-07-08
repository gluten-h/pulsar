#pragma once

#include "grng_shader.h"


class grng_geom_shader : public GRNG_SHADER
{
private:
	ID3D11GeometryShader	*shader = NULL;


	void		remove_geom_shader_memory();
	void		remove_shader_memory();
	void		set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);

	void		copy_assign(const grng_geom_shader &s);

public:
	grng_geom_shader	&operator=(const grng_geom_shader &s);
	grng_geom_shader(const grng_geom_shader &s);
	grng_geom_shader();
	grng_geom_shader(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines);
	~grng_geom_shader();

	void		set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) override;

	static GRNG_BINDABLE		*create_manager_ptr();

	void		bind() override
	{
		this->device_context->GSSetShader(this->shader, NULL, 0u);
	}

	const void	*get_shader() const
	{
		return ((void*)this->shader);
	}
};

using GRNG_GEOM_SHADER = grng_geom_shader;
