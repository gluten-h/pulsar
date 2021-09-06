#pragma once

#include "exception.h"

#include <Windows.h>
#include <comdef.h>


namespace PULSAR
{
	class WIN_EXCEPTION : public PULSAR::EXCEPTION
	{
	private:
		HRESULT		hr;

	public:
		WIN_EXCEPTION(const WIN_EXCEPTION &&e) = delete;
		WIN_EXCEPTION(const WIN_EXCEPTION &e) = delete;
		WIN_EXCEPTION() = delete;
		WIN_EXCEPTION(int line, LPCTSTR file, HRESULT hr) noexcept;

		const char		*what() const noexcept override;
		std::string		get_type() const noexcept override;
		std::string		get_error_string(HRESULT hr) const noexcept;
	};
}
