#pragma once

#include "grng_resource_manager.h"

#include <stdlib.h>


#define WIDE2(x) L##x
#define WIDE1(x) WIDE2(x)
#define __WFILE__ WIDE1(__FILE__)



#define EXC_CATCH																					\
catch (const GRNG_EXCEPTION &exc)																	\
{																									\
	MessageBoxA(NULL, exc.what(), exc.get_type().c_str(), MB_OK | MB_ICONEXCLAMATION);				\
	GRNG_RESOURCE_MANAGER::terminate();																\
	exit(EXIT_FAILURE);																				\
}																									\
catch (const std::exception &exc)																	\
{																									\
	MessageBoxA(NULL, exc.what(), "STANDART EXCEPTION", MB_OK | MB_ICONEXCLAMATION);				\
	GRNG_RESOURCE_MANAGER::terminate();																\
	exit(EXIT_FAILURE);																				\
}																									\
catch (...)																							\
{																									\
	MessageBoxA(NULL, "NO DETAILS AVAILABLE", "UNKNOWN EXCEPTION", MB_OK | MB_ICONEXCLAMATION);		\
	GRNG_RESOURCE_MANAGER::terminate();																\
	exit(EXIT_FAILURE);																				\
}
