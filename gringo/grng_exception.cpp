
#include "grng_exception.h"


grng_exception::grng_exception(int line, LPCTSTR file) noexcept
{
	this->line = line;
	this->file = file;
}

const char				*grng_exception::what() const noexcept
{
	std::ostringstream oss;

	oss << this->get_type() << "\n" << this->get_origin_string();
	this->what_buffer = oss.str();

	return (this->what_buffer.c_str());
}

std::string		grng_exception::get_type() const noexcept
{
	return (std::string("GRNG_EXCEPTION"));
}

std::string		grng_exception::get_origin_string() const noexcept
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
