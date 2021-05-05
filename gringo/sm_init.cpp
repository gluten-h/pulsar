
#include "grng_shader_manager.h"


void			grng_sm::init_d3d()
{
	grng_sm::device = GRNG_D3D::get_device();
}

void			grng_sm::init_shader()
{
	grng_sm::ishader = grng_sm::shader.get_ipiston();
}
