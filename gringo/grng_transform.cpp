
#include "grng_transform.h"


XMMATRIX											grng_transform::cam_view_matrix = XMMatrixIdentity();
XMMATRIX											grng_transform::cam_proj_matrix = XMMatrixIdentity();

GRNG_TRANSFORM_SHADER								grng_transform::transform_shader;
GRNG_VERT_CONST_BUFFER<GRNG_TRANSFORM_SHADER>		grng_transform::transform_cbuffer;
