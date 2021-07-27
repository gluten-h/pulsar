#pragma once

#include "grng_def_exc_macros.h"
#include "grng_win_exception.h"


#ifdef UNICODE
#define GRNG_WIN_EXC(hr) GRNG_WIN_EXCEPTION(__LINE__, __WFILE__, hr)
#else
#define GRNG_WIN_EXC(hr) GRNG_WIN_EXCEPTION(__LINE__, __FILE__, hr)
#endif

#ifdef UNICODE
#define GRNG_WIN_LAST_EXC() GRNG_WIN_EXCEPTION(__LINE__, __WFILE__, GetLastError())
#else
#define GRNG_WIN_LAST_EXC(hr) GRNG_WIN_EXCEPTION(__LINE__, __FILE__, GetLastError())
#endif



#define GRNG_THROW_WIN_EXC(hr)																		\
try																									\
{																									\
	throw GRNG_WIN_EXC(hr);																			\
}																									\
EXC_CATCH																							\

#define GRNG_THROW_WIN_LAST_EXC()																	\
try																									\
{																									\
	throw GRNG_WIN_LAST_EXC();																		\
}																									\
EXC_CATCH																							\



#define GRNG_WIN_ASSERT(hr) if (hr != S_OK) GRNG_THROW_WIN_EXC(hr)
