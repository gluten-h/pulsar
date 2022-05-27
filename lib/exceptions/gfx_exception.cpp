
#include "gfx_exception.h"


pulsar::gfx_exception::gfx_exception(int line, LPCTSTR file, HRESULT hr) noexcept : pulsar::base_exception(line, file)
{
	this->m_hr = hr;
}

const char		*pulsar::gfx_exception::what() const noexcept
{
	std::ostringstream oss;

	oss << this->get_type()
		<< "\n[ERROR CODE] 0x"
		<< std::setfill('0') << std::setw(sizeof(this->m_hr) * 2)
		<< std::uppercase << std::hex << this->m_hr << std::nouppercase
		<< "\n[ERROR] " << this->get_error_string()
		<< "\n[ERROR DESCRIPTION] " << this->get_error_descriprtion()
		<< "\n\n" << this->get_origin_string();
	this->m_what_buffer = oss.str();

	return (this->m_what_buffer.c_str());
}

std::string		pulsar::gfx_exception::get_type() const noexcept
{
	return (std::string("gfx_exception"));
}

std::string		pulsar::gfx_exception::get_error_string() const noexcept
{
	std::string err_str;

#ifdef UNICODE
	std::wstring wstr;
	wstr = DXGetErrorString(this->m_hr);
	err_str = std::string(wstr.begin(), wstr.end());
#else
	err_str = DXGetErrorString(this->m_hr);
#endif

	return (err_str);
}

std::string		pulsar::gfx_exception::get_error_descriprtion() const noexcept
{
	std::string err_desc;

#ifdef UNICODE
	std::wstring wstr;
	wstr = DXGetErrorDescription(this->m_hr);
	err_desc = std::string(wstr.begin(), wstr.end());
#else
	err_desc = DXGetErrorDescription(this->m_hr);
#endif

	return (err_desc);
}
