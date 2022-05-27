#pragma once

#include <exception>
#include <string>
#include <sstream>
#include <iomanip>

#include <Windows.h>


#define WIDE2(x) L##x
#define WIDE1(x) WIDE2(x)
#define __WFILE__ WIDE1(__FILE__)

namespace pulsar
{
	class base_exception : public std::exception
	{
	private:
		int m_line;
		std::string m_type;

	#ifdef UNICODE
		std::wstring m_file;
	#else
		std::string m_file;
	#endif

	protected:
		mutable std::string	m_what_buffer;

	public:
		base_exception(const exception &&e) = delete;
		base_exception(const exception &e) = delete;
		base_exception() = delete;
		base_exception(int line, LPCTSTR file) noexcept;

		const char	*what() const noexcept override;
		virtual std::string		get_type() const noexcept;
		std::string		get_origin_string() const noexcept;
	};
}
