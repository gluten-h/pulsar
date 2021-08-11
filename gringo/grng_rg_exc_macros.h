#pragma once

#include "grng_def_exc_macros.h"
#include "grng_rg_exception.h"


#ifdef UNICODE
#define GRNG_RG_EXC(err_msg) GRNG_RG_EXCEPTION(__LINE__, __WFILE__, err_msg)
#else
#define GRNG_RG_EXC(err_msg) GRNG_RG_EXCEPTION(__LINE__, __FILE__, err_msg)
#endif



#define GRNG_THROW_RG_EXC(err_msg)																	\
try																									\
{																									\
	throw GRNG_RG_EXC(err_msg);																		\
}																									\
EXC_CATCH																							\
