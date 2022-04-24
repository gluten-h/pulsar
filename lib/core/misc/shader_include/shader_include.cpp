
#include "shader_include.h"
#include "def_system.h"

#include <sstream>
#include <fstream>
#include <iostream>


bool	PULSAR::shader_include::m_is_initialized = false;


std::vector<std::filesystem::path>	&PULSAR::shader_include::include_dirs()
{
	static std::vector<std::filesystem::path> include_dirs;

	if (!shader_include::m_is_initialized)
	{
		shader_include::m_is_initialized = true;

		std::wstringstream ss(PULSAR_SHADER_INCLUDE_DIRS);
		std::wstring line;
		while (std::getline(ss, line, PULSAR_SHADER_INCLUDE_DIRS_DELIM))
			include_dirs.push_back(std::filesystem::path(line));
	}

	return (include_dirs);
}

std::wstring	PULSAR::shader_include::absolute_path(const LPCSTR path)
{
	for (auto &p : shader_include::include_dirs())
	{
		std::filesystem::path fs_path = p;
		fs_path.append(path);
		fs_path.make_preferred();

		if (std::filesystem::exists(fs_path))
			return (fs_path.wstring());
	}
	if (std::filesystem::exists(path))
	{
		std::string path_str(path);
		return (std::wstring(path_str.begin(), path_str.end()));
	}

	return (std::wstring());
}

HRESULT		PULSAR::shader_include::Open(D3D_INCLUDE_TYPE include_type, LPCSTR p_file_name, LPCVOID p_parent_data, LPCVOID *pp_data, UINT *p_bytes)
{
	std::wstring path;
	if (include_type == D3D_INCLUDE_LOCAL)
		path = shader_include::absolute_path(p_file_name);
	else if (include_type == D3D_INCLUDE_SYSTEM)
		return (E_FAIL);
	else
		return (E_FAIL);

	if (!std::filesystem::exists(path))
		return (E_FAIL);

	std::ifstream fd(path);
	std::string file_data((std::istreambuf_iterator<char>(fd)), std::istreambuf_iterator<char>());

	*pp_data = (void*)_strdup(file_data.c_str());
	*p_bytes = (UINT)file_data.size();

	return (S_OK);
}

HRESULT		PULSAR::shader_include::Close(LPCVOID p_data)
{
	free((void*)p_data);
	return (S_OK);
}
