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
	}
}
