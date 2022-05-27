#pragma once

#include <DirectXMath.h>

using namespace DirectX;


XMFLOAT3    operator*(const XMFLOAT3 &lhs, const XMFLOAT3 &rhs);
XMFLOAT3    operator*(const XMFLOAT3 &lhs, float rhs);
XMFLOAT3    operator*(float lhs, const XMFLOAT3 &rhs);
XMFLOAT3	operator+(const XMFLOAT3 &lhs, const XMFLOAT3 &rhs);
XMFLOAT3	operator-(const XMFLOAT3 &lhs, const XMFLOAT3 &rhs);

namespace pulsar
{
	float		lerp(float a, float b, float s);

	float		deg2rad(float deg);
	float		rad2deg(float rad);
}