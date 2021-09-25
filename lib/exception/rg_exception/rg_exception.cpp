
#include "rg_exception.h"


PULSAR::RG_EXCEPTION::RG_EXCEPTION(int line, LPCTSTR file, const std::string &err_msg) noexcept : PULSAR::EXCEPTION(line, file)
{
	this->err_msg = err_msg;
}

const char		*PULSAR::RG_EXCEPTION::what() const noexcept
{
	std::ostringstream oss;

	oss << this->get_type()
		<< "\n[ERROR MESSAGE] " << this->err_msg
		<< "\n\n" << this->get_origin_string();
	this->what_buffer = oss.str();

	return (this->what_buffer.c_str());
}

std::string		PULSAR::RG_EXCEPTION::get_type() const noexcept
{
	return (std::string("RENDER_GRAPH_EXCEPTION"));
}
