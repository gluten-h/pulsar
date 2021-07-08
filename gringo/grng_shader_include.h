#pragma once

#include "grng_id3d.h"

#include <iostream>
#include <fstream>
#include <string>


class grng_shader_include : public ID3DInclude
{
public:
	grng_shader_include(){ }


	HRESULT		Open(D3D_INCLUDE_TYPE include_type, LPCSTR p_file_name, LPCVOID p_parent_data, LPCVOID *pp_data, UINT *p_bytes)
	{
		const char *path = NULL;
		if (include_type == D3D_INCLUDE_LOCAL)
			path = p_file_name;
		else
			return (E_FAIL);

		std::ifstream fd(path);
		if (!fd)
			return (E_FAIL);

		std::string file_data;
		std::string line;
		while (std::getline(fd, line, '\n'))
			file_data += line;

		*pp_data = (void*)_strdup(file_data.c_str());
		*p_bytes = (UINT)file_data.size();

		return (S_OK);
	}

	HRESULT		Close(LPCVOID p_data)
	{
		free((void*)p_data);
		return (S_OK);
	}
};

using GRNG_SHADER_INCLUDE = grng_shader_include;
