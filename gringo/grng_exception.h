#pragma once

#include <exception>
#include <string>
#include <sstream>
#include <iomanip>

#include <Windows.h>


class grng_exception : public std::exception
{
private:
	int				line;
	std::string		type;

#ifdef UNICODE
	std::wstring	file;
#else
	std::string		file;
#endif
	
protected:
	mutable std::string		what_buffer;

public:
	grng_exception(const grng_exception &&e) = delete;
	grng_exception(const grng_exception &e) = delete;
	grng_exception() = delete;
	grng_exception(int line, LPCTSTR file) noexcept;

	const char				*what() const noexcept override;
	virtual std::string		get_type() const noexcept;
	std::string				get_origin_string() const noexcept;
};

using GRNG_EXCEPTION = grng_exception;
