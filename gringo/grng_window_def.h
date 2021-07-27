#pragma once

#include <Windows.h>


#define GRNG_MAX_WIN_COUNT 16

#ifdef UNICODE
#define GRNG_WIN_CLASS_NAME L"gringo"
#else
#define GRNG_WIN_CLASS_NAME "gringo"
#endif


typedef void (*GRNG_WIN_PROC_DEF)(UINT, WPARAM, void*);
typedef void (*GRNG_WIN_UPDATE_DEF)(void*);
