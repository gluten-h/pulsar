#pragma once

#include "grng_id3d.h"

#include <iostream>
#include <fstream>
#include <filesystem>
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
			return (E_FAIL);										//	TODO: IMPLEMENT THIS

		if (!std::filesystem::exists(path))
			return (E_FAIL);

		std::ifstream fd(path);
		std::stringstream buffer;
		buffer << fd.rdbuf();
		std::string file_data = buffer.str();

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
