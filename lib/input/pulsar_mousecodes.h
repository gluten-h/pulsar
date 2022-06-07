#pragma once

#include <stdint.h>


namespace pulsar
{
	using mousecode = uint16_t;
	enum : mousecode
	{
		LMB			= 0x00,
		RMB			= 0x03,
		MMB			= 0x06,
	};
}
