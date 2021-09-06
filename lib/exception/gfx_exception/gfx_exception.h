#pragma once

#include "exception.h"

#include <DxErr.h>


namespace PULSAR
{
	class GFX_EXCEPTION : public PULSAR::EXCEPTION
	{
	private:
		HRESULT hr;

	public:
		GFX_EXCEPTION(const GFX_EXCEPTION &&e) = delete;
		GFX_EXCEPTION(const GFX_EXCEPTION &e) = delete;
		GFX_EXCEPTION() = delete;
		GFX_EXCEPTION(int line, LPCTSTR file, HRESULT hr) noexcept;

		const char		*what() const noexcept override;
		std::string		get_type() const noexcept override;
		std::string		get_error_string() const noexcept;
		std::string		get_error_descriprtion() const noexcept;
	};
}
