#pragma once

#include <Windows.h>


#define GRNG_MAX_WIN_COUNT 16
#define GRNG_WIN_CLASS_NAME L"gringo"


typedef void (*GRNG_WIN_PROC_DEF)(UINT, WPARAM, void*);
typedef void (*GRNG_WIN_UPDATE_DEF)(void*);
