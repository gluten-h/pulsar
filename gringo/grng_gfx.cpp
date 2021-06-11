
#include "grng_gfx.h"


int							grng_gfx::curr_win_id = 0;
HWND						grng_gfx::curr_hwnd = NULL;

float									grng_gfx::delta_time = 0.0f;
float									grng_gfx::fps = 0.0f;
time_point<high_resolution_clock>		grng_gfx::last_frame_time = high_resolution_clock::now();

GRNG_CAMERA					*grng_gfx::curr_camera = NULL;
