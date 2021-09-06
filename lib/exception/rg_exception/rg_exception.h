#pragma once

#include "exception.h"


namespace PULSAR
{
	class RG_EXCEPTION : public PULSAR::EXCEPTION
	{
	private:
		std::string		err_msg;

	public:
		RG_EXCEPTION(const RG_EXCEPTION &&e) = delete;
		RG_EXCEPTION(const RG_EXCEPTION &e) = delete;
		RG_EXCEPTION() = delete;
		RG_EXCEPTION(int line, LPCTSTR file, const std::string &err_msg) noexcept;

		const char		*what() const noexcept override;
		std::string		get_type() const noexcept override;
	};
}
