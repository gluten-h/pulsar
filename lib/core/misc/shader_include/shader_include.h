#pragma once

#include "pulsar_id3d.h"
#include "def_system.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <filesystem>
#include <vector>


namespace PULSAR
{
	class SHADER_INCLUDE : public ID3DInclude
	{
	private:
		static bool		is_initialized;


		static std::vector<std::filesystem::path>	&include_dirs()
		{
			static std::vector<std::filesystem::path> include_dirs;
			
			if (!SHADER_INCLUDE::is_initialized)
			{
				SHADER_INCLUDE::is_initialized = true;

				std::wstringstream ss(PULSAR_SHADER_INCLUDE_DIRS);
				std::wstring line;
				while (std::getline(ss, line, PULSAR_SHADER_INCLUDE_DIRS_DELIM))
					include_dirs.push_back(std::filesystem::path(line));
			}

			return (include_dirs);
		}

		static std::wstring		file_path(const LPCSTR path)
		{
			for (auto &p : SHADER_INCLUDE::include_dirs())
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

	public:
		SHADER_INCLUDE(){ }


		HRESULT		Open(D3D_INCLUDE_TYPE include_type, LPCSTR p_file_name, LPCVOID p_parent_data, LPCVOID *pp_data, UINT *p_bytes)
		{
			std::wstring path;
			if (include_type == D3D_INCLUDE_LOCAL)
				path = SHADER_INCLUDE::file_path(p_file_name);
			else
				return (E_FAIL);										//	TODO: IMPLEMENT THIS

			if (!std::filesystem::exists(path))
				return (E_FAIL);

			std::ifstream fd(path);
			std::string file_data((std::istreambuf_iterator<char>(fd)), std::istreambuf_iterator<char>());

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
}
