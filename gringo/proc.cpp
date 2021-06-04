
#include <Windows.h>


void		cam_look_proc(UINT msg, void *data)
{
	switch (msg)
	{
		case WM_RBUTTONDOWN:
		{
			int *ref = (int*)data;
			*ref = 0;
			break;
		}
		case WM_RBUTTONUP:
		{
			int *ref = (int*)data;
			*ref = 1;
			break;
		}

		default:
			break;
	}
}
