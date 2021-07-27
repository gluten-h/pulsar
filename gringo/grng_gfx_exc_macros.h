#pragma once

#include "grng_def_exc_macros.h"
#include "grng_gfx_exception.h"


#ifdef UNICODE
#define GRNG_GFX_EXC(hr) GRNG_GFX_EXCEPTION(__LINE__, __WFILE__, hr)
#else
#define GRNG_GFX_EXC(hr) GRNG_GFX_EXCEPTION(__LINE__, __FILE__, hr)
#endif

#ifdef UNICODE
#define GRNG_GFX_LAST_EXC() GRNG_GFX_EXCEPTION(__LINE__, __WFILE__, GetLastError())
#else
#define GRNG_GFX_LAST_EXC(hr) GRNG_GFX_EXCEPTION(__LINE__, __FILE__, GetLastError())
#endif



#define GRNG_THROW_GFX_EXC(hr)																		\
try																									\
{																									\
	throw GRNG_GFX_EXC(hr);																			\
}																									\
EXC_CATCH																							\

#define GRNG_THROW_GFX_LAST_EXC()																	\
try																									\
{																									\
	throw GRNG_GFX_LAST_EXC();																		\
}																									\
EXC_CATCH																							\



#define GRNG_GFX_ASSERT(hr) if (hr != S_OK) GRNG_THROW_GFX_EXC(hr)
