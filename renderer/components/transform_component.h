#pragma once

#include <D3DX10math.h>
#include <DirectXMath.h>


namespace PULSAR
{
	class transform_component
	{
	private:
		DirectX::XMMATRIX m_mat;

	public:
		transform_component() = default;
	};
}
