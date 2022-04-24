#pragma once

#include "def_exc_macros.h"
#include "win_exception.h"


#ifdef UNICODE
#define WIN_EXC(hr) PULSAR::win_exception(__LINE__, __WFILE__, hr)
#else
#define WIN_EXC(hr) PULSAR::win_exception(__LINE__, __FILE__, hr)
#endif

#ifdef UNICODE
#define WIN_LAST_EXC() PULSAR::win_exception(__LINE__, __WFILE__, GetLastError())
#else
#define WIN_LAST_EXC(hr) PULSAR::win_exception(__LINE__, __FILE__, GetLastError())
#endif


#define THROW_WIN_EXC(hr) throw WIN_EXC(hr)
#define THROW_WIN_LAST_EXC() throw WIN_LAST_EXC()

#define WIN_ASSERT(hr) if (hr != S_OK) THROW_WIN_EXC(hr)
