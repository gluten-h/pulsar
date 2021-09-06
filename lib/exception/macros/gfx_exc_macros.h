#pragma once

#include "def_exc_macros.h"
#include "gfx_exception.h"


#ifdef UNICODE
#define GFX_EXC(hr) GFX_EXCEPTION(__LINE__, __WFILE__, hr)
#else
#define GFX_EXC(hr) GFX_EXCEPTION(__LINE__, __FILE__, hr)
#endif

#ifdef UNICODE
#define GFX_LAST_EXC() GFX_EXCEPTION(__LINE__, __WFILE__, GetLastError())
#else
#define GFX_LAST_EXC(hr) GFX_EXCEPTION(__LINE__, __FILE__, GetLastError())
#endif



#define THROW_GFX_EXC(hr)																			\
try																									\
{																									\
	throw GFX_EXC(hr);																				\
}																									\
EXC_CATCH																							\

#define THROW_GFX_LAST_EXC()																		\
try																									\
{																									\
	throw GFX_LAST_EXC();																			\
}																									\
EXC_CATCH																							\



#define GFX_ASSERT(hr) if (hr != S_OK) THROW_GFX_EXC(hr)
