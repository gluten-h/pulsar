#pragma once

#include "def_exc_macros.h"
#include "rg_exception.h"


#ifdef UNICODE
#define RG_EXC(err_msg) RG_EXCEPTION(__LINE__, __WFILE__, err_msg)
#else
#define RG_EXC(err_msg) RG_EXCEPTION(__LINE__, __FILE__, err_msg)
#endif



#define THROW_RG_EXC(err_msg)																		\
try																									\
{																									\
	throw RG_EXC(err_msg);																			\
}																									\
EXC_CATCH