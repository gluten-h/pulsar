#pragma once

#include "rasterizer_state/rasterizer_state.h"


namespace pulsar
{
	const pulsar::rasterizer_state BACK_FACE_CULL_RS(D3D11_FILL_SOLID, D3D11_CULL_BACK);
	const pulsar::rasterizer_state FRONT_FACE_CULL_RS(D3D11_FILL_SOLID, D3D11_CULL_FRONT);
}
