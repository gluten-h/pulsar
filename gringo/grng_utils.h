#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <memory>


#define GRNG_MACRO_MAX_LEN 1024

#define GRNG_MACRO_NAME(m) #m


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
};

using GRNG_UTILS = grng_utils;
