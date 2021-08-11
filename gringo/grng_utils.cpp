
#include "grng_utils.h"


std::vector<std::string>		GRNG_UTILS::str_split(const char *str, char delim)
{
	std::stringstream			ss(str);
	std::string					line;
	std::vector<std::string>	vec;

	while (std::getline(ss, line, delim))
		vec.push_back(line);

	return (vec);
}

std::vector<std::string>		GRNG_UTILS::str_split(const std::string &str, char delim)
{
	std::stringstream			ss(str);
	std::string					line;
	std::vector<std::string>	vec;

	while (std::getline(ss, line, delim))
		vec.push_back(line);

	return (vec);
}
