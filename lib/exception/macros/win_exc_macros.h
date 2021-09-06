#pragma once

#include "def_exc_macros.h"
#include "win_exception.h"


#ifdef UNICODE
#define WIN_EXC(hr) WIN_EXCEPTION(__LINE__, __WFILE__, hr)
#else
#define WIN_EXC(hr) WIN_EXCEPTION(__LINE__, __FILE__, hr)
#endif

#ifdef UNICODE
#define WIN_LAST_EXC() WIN_EXCEPTION(__LINE__, __WFILE__, GetLastError())
#else
#define WIN_LAST_EXC(hr) WIN_EXCEPTION(__LINE__, __FILE__, GetLastError())
#endif



#define THROW_WIN_EXC(hr)																			\
try																									\
{																									\
	throw WIN_EXC(hr);																				\
}																									\
EXC_CATCH																							\

#define THROW_WIN_LAST_EXC()																		\
try																									\
{																									\
	throw WIN_LAST_EXC();																			\
}																									\
EXC_CATCH																							\



#define WIN_ASSERT(hr) if (hr != S_OK) THROW_WIN_EXC(hr)
