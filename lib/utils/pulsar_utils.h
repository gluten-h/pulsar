#pragma once

#include <string>
#include <vector>
#include <sstream>


namespace PULSAR
{
	namespace utils
	{
		std::vector<std::string>	str_split(const char *str, char delim);
		std::vector<std::string>	str_split(const std::string &str, char delim);

		std::string		str_replace_all(const std::string &str, const std::string &find, const std::string &replace);
		std::wstring	str_replace_all(const std::wstring &str, const std::wstring &find, const std::wstring &replace);
	}
}
