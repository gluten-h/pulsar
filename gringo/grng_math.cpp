
#include "grng_math.h"


XMFLOAT3    operator*(const XMFLOAT3 &lhs, const XMFLOAT3 &rhs)
{
	XMVECTOR lhs_vec(XMLoadFloat3(&lhs));
	XMVECTOR rhs_vec(XMLoadFloat3(&rhs));
	XMVECTOR vec = lhs_vec * rhs_vec;

	return (XMFLOAT3(XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec)));
}

XMFLOAT3    operator*(const XMFLOAT3 &lhs, float rhs)
{
	XMVECTOR lhs_vec(XMLoadFloat3(&lhs));
	XMVECTOR vec = lhs_vec * rhs;

	return (XMFLOAT3(XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec)));
}

XMFLOAT3    operator*(float lhs, const XMFLOAT3 &rhs)
{
	XMVECTOR rhs_vec(XMLoadFloat3(&rhs));
	XMVECTOR vec = lhs * rhs_vec;

	return (XMFLOAT3(XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec)));
}

XMFLOAT3	operator+(const XMFLOAT3 &lhs, const XMFLOAT3 &rhs)
{
	XMVECTOR lhs_vec(XMLoadFloat3(&lhs));
	XMVECTOR rhs_vec(XMLoadFloat3(&rhs));
	XMVECTOR vec = lhs_vec + rhs_vec;

	return (XMFLOAT3(XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec)));
}

XMFLOAT3	operator-(const XMFLOAT3 &lhs, const XMFLOAT3 &rhs)
{
	XMVECTOR lhs_vec(XMLoadFloat3(&lhs));
	XMVECTOR rhs_vec(XMLoadFloat3(&rhs));
	XMVECTOR vec = lhs_vec - rhs_vec;

	return (XMFLOAT3(XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec)));
}


float		grng_lerp(float a, float b, float s)
{
	return (a + (b - a) * s);
}


float		grng_deg2rad(float deg)
{
	return (deg * D3DX_PI / 180.0f);
}

float		grng_rad2deg(float rad)
{
	return (rad * 180.0f / D3DX_PI);
}
