#pragma once

#include <exception>
#include <string>
#include <sstream>
#include <iomanip>

#include <Windows.h>


namespace PULSAR
{
	class EXCEPTION : public std::exception
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
		EXCEPTION(const exception &&e) = delete;
		EXCEPTION(const exception &e) = delete;
		EXCEPTION() = delete;
		EXCEPTION(int line, LPCTSTR file) noexcept;

		const char				*what() const noexcept override;
		virtual std::string		get_type() const noexcept;
		std::string				get_origin_string() const noexcept;
	};
}
