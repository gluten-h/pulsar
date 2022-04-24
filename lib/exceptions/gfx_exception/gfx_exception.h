#pragma once

#include "base_exception.h"

#include <DxErr.h>


namespace PULSAR
{
	class gfx_exception : public PULSAR::base_exception
	{
	private:
		HRESULT m_hr;

	public:
		gfx_exception(const gfx_exception &&e) = delete;
		gfx_exception(const gfx_exception &e) = delete;
		gfx_exception() = delete;
		gfx_exception(int line, LPCTSTR file, HRESULT hr) noexcept;

		const char		*what() const noexcept override;
		std::string		get_type() const noexcept override;
		std::string		get_error_string() const noexcept;
		std::string		get_error_descriprtion() const noexcept;
	};
}
