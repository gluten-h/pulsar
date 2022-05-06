
#include "rg_exception.h"


PULSAR::rg_exception::rg_exception(int line, LPCTSTR file, const std::string &err_msg) noexcept : PULSAR::base_exception(line, file)
{
	this->m_err_msg = err_msg;
}

const char		*PULSAR::rg_exception::what() const noexcept
{
	std::ostringstream oss;

	oss << this->get_type()
		<< "\n[ERROR MESSAGE] " << this->m_err_msg
		<< "\n\n" << this->get_origin_string();
	this->m_what_buffer = oss.str();

	return (this->m_what_buffer.c_str());
}

std::string		PULSAR::rg_exception::get_type() const noexcept
{
	return (std::string("RENDER_GRAPH_EXCEPTION"));
}
