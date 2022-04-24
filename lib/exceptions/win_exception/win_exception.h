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
