#pragma once

#include <Windows.h>


namespace PULSAR
{
	const struct
	{
		const LPCTSTR class_name = __T("pulsar");
		const LPCSTR name = "pulsar";
		const DWORD style = WS_VISIBLE | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU;
		int width = 1280;
		int height = 720;
	}	DEFAULT_WINDOW_SETTINGS;
}
