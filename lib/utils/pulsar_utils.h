#pragma once

#include <string>
#include <vector>


namespace PULSAR
{
	namespace utils
	{
		std::vector<std::string>	str_split(const char *str, char delim);
		std::vector<std::string>	str_split(const std::string &str, char delim);
	}
}
