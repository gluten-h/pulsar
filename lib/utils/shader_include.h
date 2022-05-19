#pragma once

#include "gfx/gfx.h"

#include <filesystem>
#include <string>
#include <vector>


namespace PULSAR
{
	class shader_include : public ID3DInclude
	{
	private:
		static bool m_is_initialized;

	private:
		static std::vector<std::filesystem::path>	&include_dirs();
		static std::wstring		absolute_path(const LPCSTR path);

	public:
		HRESULT		Open(D3D_INCLUDE_TYPE include_type, LPCSTR p_file_name, LPCVOID p_parent_data, LPCVOID *pp_data, UINT *p_bytes);
		HRESULT		Close(LPCVOID p_data);
	};
}
