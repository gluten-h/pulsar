#pragma once

#include "grng_d3d.h"


XMFLOAT3    operator*(const XMFLOAT3 &lhs, const XMFLOAT3 &rhs);
XMFLOAT3    operator*(const XMFLOAT3 &lhs, float rhs);
XMFLOAT3    operator*(float lhs, const XMFLOAT3 &rhs);
XMFLOAT3	operator+(const XMFLOAT3 &lhs, const XMFLOAT3 &rhs);
XMFLOAT3	operator-(const XMFLOAT3 &lhs, const XMFLOAT3 &rhs);