
#include "grng_rg_exception.h"


grng_rg_exception::grng_rg_exception(int line, LPCTSTR file, const std::string &err_msg) noexcept : GRNG_EXCEPTION(line, file)
{
	this->err_msg = err_msg;
}

const char			*grng_rg_exception::what() const noexcept
{
	std::ostringstream oss;

	oss << this->get_type()
		<< "[ERROR MESSAGE] " << this->err_msg
		<< "\n\n" << this->get_origin_string();
	this->what_buffer = oss.str();

	return (this->what_buffer.c_str());
}

std::string			grng_rg_exception::get_type() const noexcept
{
	return (std::string("GRNG_RENDER_GRAPH_EXCEPTION"));
}
