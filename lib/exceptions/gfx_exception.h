#pragma once

#include "base_exception.h"
#include <DxErr.h>


namespace pulsar
{
	class gfx_exception : public pulsar::base_exception
	{
	private:
		HRESULT m_hr;

	public:
		gfx_exception(const gfx_exception &&e) = delete;
		gfx_exception(const gfx_exception &e) = delete;
		gfx_exception() = delete;
		gfx_exception(int line, LPCTSTR file, HRESULT hr) noexcept;

		const char		*what() const noexcept override;
		std::string		get_type() const noexcept override;
		std::string		get_error_string() const noexcept;
		std::string		get_error_descriprtion() const noexcept;
	};
}


#ifdef UNICODE
#define GFX_EXC(hr) pulsar::gfx_exception(__LINE__, __WFILE__, hr)
#else
#define GFX_EXC(hr) pulsar::gfx_exception(__LINE__, __FILE__, hr)
#endif

#ifdef UNICODE
#define LAST_GFX_EXC() pulsar::gfx_exception(__LINE__, __WFILE__, GetLastError())
#else
#define LAST_GFX_EXC(hr) pulsar::gfx_exception(__LINE__, __FILE__, GetLastError())
#endif


#define THROW_GFX_EXC(hr) throw GFX_EXC(hr)
#define THROW_LAST_GFX_EXC() throw LAST_GFX_EXC()

#ifdef _DEBUG
#define GFX_ASSERT(hr) if (hr != S_OK) THROW_GFX_EXC(hr)
#else
#define GFX_ASSERT(hr) hr
#endif
