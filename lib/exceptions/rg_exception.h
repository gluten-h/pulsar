#pragma once

#include "base_exception.h"


namespace pulsar
{
	class rg_exception : public pulsar::base_exception
	{
	private:
		std::string m_err_msg;

	public:
		rg_exception(const rg_exception &&e) = delete;
		rg_exception(const rg_exception &e) = delete;
		rg_exception() = delete;
		rg_exception(int line, LPCTSTR file, const std::string &err_msg) noexcept;

		const char		*what() const noexcept override;
		std::string		get_type() const noexcept override;
	};
}


#ifdef UNICODE
#define RG_EXC(err_msg) pulsar::rg_exception(__LINE__, __WFILE__, err_msg)
#else
#define RG_EXC(err_msg) pulsar::rg_exception(__LINE__, __FILE__, err_msg)
#endif

#define THROW_RG_EXC(err_msg) throw RG_EXC(err_msg)
