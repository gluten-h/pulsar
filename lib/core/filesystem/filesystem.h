#pragma once

#include <Windows.h>
#include <filesystem>
#include <string>
#include <unordered_map>


namespace PULSAR
{
	class FILESYSTEM
	{
	private:
		static std::unordered_map<size_t, std::filesystem::path>	&mount_points()
		{
			static std::filesystem::path project_path(PULSAR_ROOT_PATH);
			static std::unordered_map<size_t, std::filesystem::path> mount_points({		{ std::filesystem::hash_value(project_path), project_path }		});

			return (mount_points);
		}

	public:
		static std::wstring		file_path(const LPCWSTR path)
		{
			for (auto &p : FILESYSTEM::mount_points())
			{
				std::filesystem::path fs_path = p.second;
				fs_path.append(path);
				fs_path.make_preferred();

				if (std::filesystem::exists(fs_path))
					return (fs_path.wstring());
			}
			if (std::filesystem::exists(path))
				return (std::wstring(path));

			return (std::wstring());
		}
	};
}
