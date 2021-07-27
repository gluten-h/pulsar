#pragma once

#include "grng_exception.h"

#include <Windows.h>
#include <comdef.h>


class grng_win_exception : public GRNG_EXCEPTION
{
private:
	HRESULT hr;

public:
	grng_win_exception(const grng_win_exception &&e) = delete;
	grng_win_exception(const grng_win_exception &e) = delete;
	grng_win_exception() = delete;
	grng_win_exception(int line, LPCTSTR file, HRESULT hr) noexcept;

	const char		*what() const noexcept override;
	std::string		get_type() const noexcept override;
	std::string		get_error_string(HRESULT hr) const noexcept;
};

using GRNG_WIN_EXCEPTION = grng_win_exception;
