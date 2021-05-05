#pragma once

#include <string>
#include <vector>
#include <sstream>


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
