
#include "gfx.h"


PULSAR::WINDOW		*PULSAR::GFX::curr_win = NULL;
HWND				PULSAR::GFX::curr_hwnd = NULL;

float									PULSAR::GFX::delta_time = 0.0f;
float									PULSAR::GFX::fps = 0.0f;
time_point<high_resolution_clock>		PULSAR::GFX::last_frame_time = high_resolution_clock::now();

PULSAR::CAMERA		*PULSAR::GFX::curr_camera = NULL;
