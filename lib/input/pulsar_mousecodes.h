#pragma once

#include <stdint.h>


namespace pulsar
{
	using mouse_code = uint16_t;
	enum : mouse_code
	{
		LMB			= 0x00,
		RMB			= 0x03,
		MMB			= 0x06,
	};
}
