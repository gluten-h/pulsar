#pragma once

#include "grng_bindable.h"
#include "grng_shader_include.h"

#include <iostream>
#include <fstream>


#define GRNG_VERT_SHADER_TARGET "vs_5_0"
#define GRNG_GEOM_SHADER_TARGET "gs_5_0"
#define GRNG_FRAG_SHADER_TARGET "ps_5_0"


#define GRNG_VERT_ENTRY "vert"
#define GRNG_GEOM_ENTRY "geom"
#define GRNG_FRAG_ENTRY "frag"


class grng_shader : public GRNG_BINDABLE
{
protected:
	ID3DBlob		*shader_blob = NULL;


	void			remove_shader_memory();
	void			set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target, const D3D_SHADER_MACRO *defines);

public:
	grng_shader		&operator=(const grng_shader &s) = delete;
	grng_shader(const grng_shader &s) = delete;
	grng_shader() : GRNG_BINDABLE(){ }
	~grng_shader()
	{
		this->remove_shader_memory();
	}

	ID3DBlob		*get_shader_blob() const
	{
		return (this->shader_blob);
	}

	virtual void		set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) = 0;
	virtual const void	*get_shader() const = 0;
};

using GRNG_SHADER = grng_shader;
