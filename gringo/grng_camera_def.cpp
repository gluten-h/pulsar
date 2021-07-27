
#include "grng_camera.h"


GRNG_FRAG_CONST_BUFFER<GRNG_CAMERA_DEFERRED_SHADER>			grng_camera::cam_deferred_cbuffer;
GRNG_CAMERA_DEFERRED_SHADER									grng_camera::cam_deferred_shader;

GRNG_FRAG_CONST_BUFFER<GRNG_CAMERA_POST_EFFECTS_SHADER>		grng_camera::cam_post_effects_cbuffer;
GRNG_CAMERA_POST_EFFECTS_SHADER								grng_camera::cam_post_effects_shader;