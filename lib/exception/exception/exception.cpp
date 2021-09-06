
#include "exception.h"


PULSAR::EXCEPTION::EXCEPTION(int line, LPCTSTR file) noexcept
{
	this->line = line;
	this->file = file;
}

const char		*PULSAR::EXCEPTION::what() const noexcept
{
	std::ostringstream oss;

	oss << this->get_type() << "\n" << this->get_origin_string();
	this->what_buffer = oss.str();

	return (this->what_buffer.c_str());
}

std::string		PULSAR::EXCEPTION::get_type() const noexcept
{
	return (std::string("EXCEPTION"));
}

std::string		PULSAR::EXCEPTION::get_origin_string() const noexcept
{
	std::string str = "[FILE] ";
#ifdef UNICODE
	std::wstring wstr;
	wstr = this->file;
	str += std::string(wstr.begin(), wstr.end());
#else
	str += this->file;
#endif
	str += "\n[LINE] " + std::to_string(this->line);

	return (str);
}
