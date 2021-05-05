
#include "grng_d3d.h"


IDXGIFactory			*grng_d3d::idxgi_factory = NULL;

ID3D11Device			*grng_d3d::device = NULL;
ID3D11DeviceContext		*grng_d3d::device_context = NULL;
