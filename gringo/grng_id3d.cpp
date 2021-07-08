
#include "grng_id3d.h"


bool						grng_id3d::is_initialized = false;

IDXGIFactory				*grng_id3d::idxgi_factory = NULL;
ID3D11Device				*grng_id3d::device = NULL;
ID3D11DeviceContext			*grng_id3d::device_context = NULL;
