#pragma once

#include "bindable.h"
#include "shader_include.h"
#include "filesystem.h"

#include <iostream>
#include <fstream>


namespace PULSAR
{
	const LPCSTR VERT_SHADER_TARGET = "vs_5_0";
	const LPCSTR GEOM_SHADER_TARGET = "gs_5_0";
	const LPCSTR FRAG_SHADER_TARGET = "ps_5_0";

	const LPCSTR VERT_SHADER_ENTRY = "vert";
	const LPCSTR GEOM_SHADER_ENTRY = "geom";
	const LPCSTR FRAG_SHADER_ENTRY = "frag";


class SHADER : public PULSAR::BINDABLE
{
protected:
	ID3DBlob	*shader_blob = NULL;


	void	remove_shader_memory();
	void	set_shader_memory(const LPCWSTR shader_file, const LPCSTR entry, const LPCSTR target, const D3D_SHADER_MACRO *defines);

public:
	SHADER &operator=(const SHADER &s) = delete;
	SHADER(const SHADER &s) = delete;
	SHADER() : PULSAR::BINDABLE(){ }
	~SHADER()
	{
		this->remove_shader_memory();
	}

	ID3DBlob *get_shader_blob() const
	{
		return (this->shader_blob);
	}

	virtual void		set(const LPCWSTR shader_file, const LPCSTR entry, const D3D_SHADER_MACRO *defines) = 0;
	virtual const void	*get_shader() const = 0;
};
}