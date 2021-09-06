
#include "gfx_exception.h"


PULSAR::GFX_EXCEPTION::GFX_EXCEPTION(int line, LPCTSTR file, HRESULT hr) noexcept : PULSAR::EXCEPTION(line, file)
{
	this->hr = hr;
}

const char		*PULSAR::GFX_EXCEPTION::what() const noexcept
{
	std::ostringstream oss;

	oss << this->get_type()
		<< "\n[ERROR CODE] 0x"
		<< std::setfill('0') << std::setw(sizeof(this->hr) * 2)
		<< std::uppercase << std::hex << this->hr << std::nouppercase
		<< "\n[ERROR] " << this->get_error_string()
		<< "\n[ERROR DESCRIPTION] " << this->get_error_descriprtion()
		<< "\n\n" << this->get_origin_string();
	this->what_buffer = oss.str();

	return (this->what_buffer.c_str());
}

std::string		PULSAR::GFX_EXCEPTION::get_type() const noexcept
{
	return (std::string("GFX_EXCEPTION"));
}

std::string		PULSAR::GFX_EXCEPTION::get_error_string() const noexcept
{
	std::string err_str;

#ifdef UNICODE
	std::wstring wstr;
	wstr = DXGetErrorString(this->hr);
	err_str = std::string(wstr.begin(), wstr.end());
#else
	err_str = DXGetErrorString(this->hr);
#endif

	return (err_str);
}

std::string		PULSAR::GFX_EXCEPTION::get_error_descriprtion() const noexcept
{
	std::string err_desc;

#ifdef UNICODE
	std::wstring wstr;
	wstr = DXGetErrorDescription(this->hr);
	err_desc = std::string(wstr.begin(), wstr.end());
#else
	err_desc = DXGetErrorDescription(this->hr);
#endif

	return (err_desc);
}
