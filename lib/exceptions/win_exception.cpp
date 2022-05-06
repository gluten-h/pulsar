
#include "win_exception.h"


PULSAR::win_exception::win_exception(int line, LPCTSTR file, HRESULT hr) noexcept : PULSAR::base_exception(line, file)
{
	this->m_hr = hr;
}

const char		*PULSAR::win_exception::what() const noexcept
{
	std::ostringstream oss;

	oss << this->get_type()
			<< "\n[ERROR CODE] 0x"
			<< std::setfill('0') << std::setw(sizeof(this->m_hr) * 2)
			<< std::uppercase << std::hex << this->m_hr << std::nouppercase
			<< "\n[ERROR DESCRIPTION] " << this->get_error_string(this->m_hr)
			<< "\n\n" << this->get_origin_string();
	this->m_what_buffer = oss.str();

	return (this->m_what_buffer.c_str());
}

std::string		PULSAR::win_exception::get_type() const noexcept
{
	return (std::string("WINDOW_EXCEPTION"));
}

std::string		PULSAR::win_exception::get_error_string(HRESULT hr) const noexcept
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
