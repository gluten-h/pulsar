#pragma once

#include <Windows.h>


namespace PULSAR
{
	const size_t MAX_WIN_COUNT = 16u;

	const LPCTSTR WIN_CLASS_NAME = __T("pulsar");

	typedef void (*WIN_PROC_DEF)(UINT, WPARAM, void*);
	typedef void (*WIN_UPDATE_DEF)(void*);
}
