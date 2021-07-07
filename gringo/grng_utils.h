#pragma once

#include <Windows.h>

#include <string>
#include <vector>
#include <sstream>
#include <memory>


class grng_utils
{
public:
	static std::vector<std::string>		str_split(const char *str, char delim)
	{
		std::stringstream			ss(str);
		std::string					line;
		std::vector<std::string>	vec;

		while (std::getline(ss, line, delim))
			vec.push_back(line);

		return (vec);
	}

	static std::string					guid_to_str(GUID &guid)
	{
		char guid_cstr[37];
		snprintf(guid_cstr, sizeof(guid_cstr),
				 "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
				 guid.Data1, guid.Data2, guid.Data3,
				 guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
				 guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);


		return (std::string(guid_cstr));
	}
};

using GRNG_UTILS = grng_utils;
