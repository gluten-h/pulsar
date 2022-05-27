
#include "base_exception.h"


pulsar::base_exception::base_exception(int line, LPCTSTR file) noexcept
{
	this->m_line = line;
	this->m_file = file;
}

const char		*pulsar::base_exception::what() const noexcept
{
	std::ostringstream oss;

	oss << this->get_type() << "\n" << this->get_origin_string();
	this->m_what_buffer = oss.str();

	return (this->m_what_buffer.c_str());
}

std::string		pulsar::base_exception::get_type() const noexcept
{
	return (std::string("base_exception"));
}

std::string		pulsar::base_exception::get_origin_string() const noexcept
{
	std::string str = "[FILE] ";
#ifdef UNICODE
	std::wstring wstr;
	wstr = this->m_file;
	str += std::string(wstr.begin(), wstr.end());
#else
	str += this->m_file;
#endif
	str += "\n[LINE] " + std::to_string(this->m_line);

	return (str);
}
