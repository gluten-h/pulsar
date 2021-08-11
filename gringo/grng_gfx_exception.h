#pragma once

#include "grng_exception.h"

#include <DxErr.h>


class grng_gfx_exception : public GRNG_EXCEPTION
{
private:
	HRESULT hr;

public:
	grng_gfx_exception(const grng_gfx_exception &&e) = delete;
	grng_gfx_exception(const grng_gfx_exception &e) = delete;
	grng_gfx_exception() = delete;
	grng_gfx_exception(int line, LPCTSTR file, HRESULT hr) noexcept;

	const char		*what() const noexcept override;
	std::string		get_type() const noexcept override;
	std::string		get_error_string() const noexcept;
	std::string		get_error_descriprtion() const noexcept;
};

using GRNG_GFX_EXCEPTION = grng_gfx_exception;
