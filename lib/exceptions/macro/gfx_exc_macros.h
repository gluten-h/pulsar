#pragma once

#include "def_exc_macros.h"
#include "gfx_exception.h"


#ifdef UNICODE
#define GFX_EXC(hr) PULSAR::gfx_exception(__LINE__, __WFILE__, hr)
#else
#define GFX_EXC(hr) PULSAR::gfx_exception(__LINE__, __FILE__, hr)
#endif

#ifdef UNICODE
#define GFX_LAST_EXC() PULSAR::gfx_exception(__LINE__, __WFILE__, GetLastError())
#else
#define GFX_LAST_EXC(hr) PULSAR::gfx_exception(__LINE__, __FILE__, GetLastError())
#endif


#define THROW_GFX_EXC(hr) throw GFX_EXC(hr)
#define THROW_GFX_LAST_EXC() throw GFX_LAST_EXC()

#define GFX_ASSERT(hr) if (hr != S_OK) THROW_GFX_EXC(hr)
