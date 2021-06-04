
#include "grng_gfx.h"


int						grng_gfx::curr_win_id = 0;
float					grng_gfx::win_fps[GRNG_MAX_WIN_COUNT] = { 0.0f };
GRNG_CAMERA				*grng_gfx::curr_camera = NULL;
