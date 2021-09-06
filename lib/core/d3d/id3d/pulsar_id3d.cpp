
#include "pulsar_id3d.h"


bool					PULSAR::PULSAR_ID3D::is_initialized = false;

IDXGIFactory			*PULSAR::PULSAR_ID3D::idxgi_factory = NULL;
ID3D11Device			*PULSAR::PULSAR_ID3D::device = NULL;
ID3D11DeviceContext		*PULSAR::PULSAR_ID3D::device_context = NULL;
