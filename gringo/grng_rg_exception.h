#pragma once

#include "grng_exception.h"


class grng_rg_exception : public GRNG_EXCEPTION
{
private:
	std::string		err_msg;

public:
	grng_rg_exception(const grng_rg_exception &&e) = delete;
	grng_rg_exception(const grng_rg_exception &e) = delete;
	grng_rg_exception() = delete;
	grng_rg_exception(int line, LPCTSTR file, const std::string &err_msg) noexcept;

	const char		*what() const noexcept override;
	std::string		get_type() const noexcept override;
};

using GRNG_RG_EXCEPTION = grng_rg_exception;
