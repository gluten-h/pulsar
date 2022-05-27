#pragma once

#include <Windows.h>
#include <filesystem>
#include <vector>


namespace pulsar
{
	class filesystem
	{
	private:
		static std::vector<std::filesystem::path>	&mount_points()
		{
			static const std::filesystem::path project_path(PULSAR_ROOT_PATH);
			static std::vector<std::filesystem::path> mount_points = { project_path };

			return (mount_points);
		}

	public:
		static std::wstring		absolute_path(const LPCWSTR relative_path)
		{
			for (auto &point : filesystem::mount_points())
			{
				std::filesystem::path fs_path = point;
				fs_path.append(relative_path);
				fs_path.make_preferred();

				if (std::filesystem::exists(fs_path))
					return (fs_path.wstring());
			}

			return (std::wstring());
		}
	};
}
