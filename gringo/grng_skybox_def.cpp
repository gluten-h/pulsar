
#include "grng_skybox.h"


GRNG_VERT_SHADER		grng_skybox::vs = GRNG_VERT_SHADER(GRNG_SKYBOX_VS_PATH, GRNG_VERT_ENTRY, NULL);
GRNG_FRAG_SHADER		grng_skybox::fs = GRNG_FRAG_SHADER(GRNG_SKYBOX_FS_PATH, GRNG_FRAG_ENTRY, NULL);

GRNG_INPUT_LAYOUT		grng_skybox::input_layout;
GRNG_SAMPLER			grng_skybox::sampler;
