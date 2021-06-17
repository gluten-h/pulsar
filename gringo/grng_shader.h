#pragma once

#include "grng_bindable.h"
#include "grng_shader_include.h"

#include <iostream>
#include <fstream>


enum class			GRNG_SHADER_TYPE
{
	GRNG_SHADER_UNSPECIFIED,
	GRNG_VERT_SHADER,
	GRNG_GEOM_SHADER,
	GRNG_FRAG_SHADER
};

#define GRNG_VERT_SHADER_TARGET "vs_5_0"
#define GRNG_GEOM_SHADER_TARGET "gs_5_0"
#define GRNG_FRAG_SHADER_TARGET "ps_5_0"


#define GRNG_VERT_ENTRY "vert"
#define GRNG_GEOM_ENTRY "geom"
#define GRNG_FRAG_ENTRY "frag"


class grng_shader : public GRNG_BINDABLE
{
protected:
	GRNG_SHADER_TYPE		type = GRNG_SHADER_TYPE::GRNG_SHADER_UNSPECIFIED;
	ID3DBlob				*shader_blob = NULL;

	void			remove_shader_memory()
	{
		if (shader_blob)
		{
			this->shader_blob->Release();
			this->shader_blob = NULL;
		}
	}

	void	set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target, const D3D_SHADER_MACRO *defines)
	{
		ID3DBlob *err_msg;
		GRNG_SHADER_INCLUDE s_inc;
		HRESULT hr = D3DCompileFromFile(shader_file, defines, &s_inc, entry, target, NULL, NULL, &this->shader_blob, &err_msg);
		if (hr != S_OK)
		{
			std::ofstream os("resources/log.txt");
			os.clear();

			const char *error = static_cast<const char*>(err_msg->GetBufferPointer());
			bool breakpoint = 1;

			os << error << '\n';

			os.close();
			exit(0);
		}
	}

public:
	grng_shader() : GRNG_BINDABLE(){ }

	~grng_shader()
	{
		this->remove_shader_memory();
	}


	ID3DBlob			*get_shader_blob() const
	{
		return (this->shader_blob);
	}

	virtual void		set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) = 0;
	virtual const void	*get_shader() const = 0;
};

using GRNG_SHADER = grng_shader;
