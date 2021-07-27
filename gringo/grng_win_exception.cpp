
#include "grng_win_exception.h"


grng_win_exception::grng_win_exception(int line, LPCTSTR file, HRESULT hr) noexcept : GRNG_EXCEPTION(line, file)
{
	this->hr = hr;
}

const char		*grng_win_exception::what() const noexcept
{
	std::ostringstream oss;

	oss << this->get_type()
			<< "\n[ERROR CODE] 0x"
			<< std::setfill('0') << std::setw(sizeof(this->hr) * 2)
			<< std::uppercase << std::hex << this->hr << std::nouppercase
			<< "\n[ERROR DESCRIPTION] " << this->get_error_string(this->hr)
			<< "\n\n" << this->get_origin_string();
	this->what_buffer = oss.str();

	return (this->what_buffer.c_str());
}

std::string		grng_win_exception::get_type() const noexcept
{
	return (std::string("GRNG_WINDOW_EXCEPTION"));
}

std::string		grng_win_exception::get_error_string(HRESULT hr) const noexcept
{
	_com_error err(hr);
	LPCTSTR err_msg = err.ErrorMessage();
	std::string err_str;

#ifdef UNICODE
	std::wstring wstr;
	wstr = err_msg;
	err_str = std::string(wstr.begin(), wstr.end());
#else
	err_str = err_msg;
#endif

	return (err_str);
}
