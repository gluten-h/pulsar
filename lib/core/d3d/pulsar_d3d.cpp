
#include "pulsar_d3d.h"


bool					PULSAR::PULSAR_D3D::is_initialized = false;

IDXGIFactory			*PULSAR::PULSAR_D3D::idxgi_factory = NULL;
ID3D11Device			*PULSAR::PULSAR_D3D::device = NULL;
ID3D11DeviceContext		*PULSAR::PULSAR_D3D::device_context = NULL;

