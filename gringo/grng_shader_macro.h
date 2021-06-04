#pragma once

#include "igrng_d3d.h"

#include <vector>


class grng_shader_macro
{
private:
	std::vector<D3D_SHADER_MACRO>		macros;

public:
	grng_shader_macro(){ }
	~grng_shader_macro()
	{
		this->macros.clear();
	}

	void		add(LPCSTR name, LPCSTR definition)
	{
		D3D_SHADER_MACRO s_macro;
		s_macro.Name = name;
		s_macro.Definition = definition;

		this->macros.push_back(s_macro);
	}

	void		add(const D3D_SHADER_MACRO &sm)
	{
		this->macros.push_back(sm);
	}


	const D3D_SHADER_MACRO		*data() const
	{
		return (this->macros.data());
	}
};

using GRNG_SHADER_MACRO = grng_shader_macro;
