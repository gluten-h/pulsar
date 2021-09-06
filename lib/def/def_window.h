#pragma once

#include <Windows.h>


namespace PULSAR
{
	const size_t MAX_WIN_COUNT = 16u;

#ifdef UNICODE
	const LPCWSTR WIN_CLASS_NAME = L"pulsar";
#else
	const LPCSTR WIN_CLASS_NAME = "pulsar";
#endif


	typedef void (*WIN_PROC_DEF)(UINT, WPARAM, void*);
	typedef void (*WIN_UPDATE_DEF)(void*);
}
