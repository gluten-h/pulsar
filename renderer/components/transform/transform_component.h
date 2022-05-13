#pragma once

#include "utils/math.h"


namespace PULSAR
{
	struct transform_component
	{
		XMMATRIX transform = XMMatrixIdentity();

		transform_component() = default;
		transform_component(const XMMATRIX &transform)
		{
			this->transform = transform;
		}
		~transform_component() = default;

		operator XMMATRIX &()
		{
			return (this->transform);
		}
	};
}
