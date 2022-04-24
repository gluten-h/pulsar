
#include "pulsar_utils.h"


std::vector<std::string>	PULSAR::utils::str_split(const char *str, char delim)
{
	std::stringstream ss(str);
	std::string line;
	std::vector<std::string> vec;

	while (std::getline(ss, line, delim))
		vec.push_back(line);

	return (vec);
}

std::vector<std::string>	PULSAR::utils::str_split(const std::string &str, char delim)
{
	std::stringstream ss(str);
	std::string line;
	std::vector<std::string> vec;

	while (std::getline(ss, line, delim))
		vec.push_back(line);

	return (vec);
}


std::string		PULSAR::utils::str_replace_all(const std::string &str, const std::string &find, const std::string &replace)
{
	std::string new_str = str;
	size_t idx = 0u;
	while (true)
	{
		idx = new_str.find(find, idx);
		if (idx == std::string::npos)
			break;

		new_str.replace(idx, replace.size(), replace);
		idx += replace.size();
	}

	return (new_str);
}

std::wstring	PULSAR::utils::str_replace_all(const std::wstring &str, const std::wstring &find, const std::wstring &replace)
{
	std::wstring new_str = str;
	size_t idx = 0u;
	while (true)
	{
		idx = new_str.find(find, idx);
		if (idx == std::string::npos)
			break;

		new_str.replace(idx, replace.size(), replace);
		idx += replace.size();
	}

	return (new_str);
}
