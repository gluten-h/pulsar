#pragma once

#include "grng_bindable.h"


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

	void	set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target)
	{
		HRESULT hr = D3DCompileFromFile(shader_file, NULL, NULL, entry, target, NULL, NULL, &this->shader_blob, NULL);
	}

public:
	grng_shader() = delete;
	grng_shader(const grng_shader &s) = delete;
	grng_shader(grng_shader &&s) = delete;
	grng_shader(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target) : GRNG_BINDABLE()
	{
		this->set_shader_memory(shader_file, entry, target);
	}

	~grng_shader()
	{
		this->remove_shader_memory();
	}


	ID3DBlob			*get_shader_blob() const
	{
		return (this->shader_blob);
	}

	virtual void		set_shader(const LPCWSTR shader_file, const LPCSTR entry) = 0;
	virtual const void	*get_shader() const = 0;
};

using GRNG_SHADER = grng_shader;
