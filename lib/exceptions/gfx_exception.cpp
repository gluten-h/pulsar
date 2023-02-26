
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
		<< "\n[ERROR DESCRIPTION] " << this->get_error_descriprtion()
		<< "\n\n" << this->get_origin_string();
	this->m_what_buffer = oss.str();

	return (this->m_what_buffer.c_str());
}

std::string		pulsar::gfx_exception::get_type() const noexcept
{
	return (std::string("gfx_exception"));
}

std::string		pulsar::gfx_exception::get_error_descriprtion() const noexcept
{
	std::string err_str;
	LPTSTR err = NULL;

	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
								NULL, this->m_hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&err, 0, NULL);

	if (!err)
		return ("Undefined error code");

#ifdef UNICODE
	std::wstring wstr = err;
	err_str = std::string(wstr.begin(), wstr.end());
#else
	err_str = err;
#endif
	LocalFree(err);

	return (err_str);
}
