#pragma once

#include "base_exception.h"

#include <Windows.h>
#include <comdef.h>


namespace PULSAR
{
	class win_exception : public PULSAR::base_exception
	{
	private:
		HRESULT m_hr;

	public:
		win_exception(const win_exception &&e) = delete;
		win_exception(const win_exception &e) = delete;
		win_exception() = delete;
		win_exception(int line, LPCTSTR file, HRESULT hr) noexcept;

		const char		*what() const noexcept override;
		std::string		get_type() const noexcept override;
		std::string		get_error_string(HRESULT hr) const noexcept;
	};
}


#ifdef UNICODE
#define WIN_EXC(hr) PULSAR::win_exception(__LINE__, __WFILE__, hr)
#else
#define WIN_EXC(hr) PULSAR::win_exception(__LINE__, __FILE__, hr)
#endif

#ifdef UNICODE
#define LAST_WIN_EXC() PULSAR::win_exception(__LINE__, __WFILE__, GetLastError())
#else
#define LAST_WIN_EXC(hr) PULSAR::win_exception(__LINE__, __FILE__, GetLastError())
#endif


#define THROW_WIN_EXC(hr) throw WIN_EXC(hr)
#define THROW_LAST_WIN_EXC() throw LAST_WIN_EXC()

#ifdef _DEBUG
#define WIN_ASSERT(hr) if (hr != S_OK) THROW_WIN_EXC(hr)
#else
#define WIN_ASSERT(hr)
#endif
