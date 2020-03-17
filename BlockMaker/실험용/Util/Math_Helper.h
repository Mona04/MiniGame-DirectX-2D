#pragma once
#include "pch.h"

static inline D3DXVECTOR3 operator*(const D3DXQUATERNION& lhs, const D3DXVECTOR3& rhs)
{
	D3DXVECTOR3 qVec(lhs.x, lhs.y, lhs.z);
	D3DXVECTOR3 cross1, cross2;
	D3DXVec3Cross(&cross1, &qVec, &rhs);
	D3DXVec3Cross(&cross2, &qVec, &cross1);

	return rhs + (cross1 * lhs.w + cross2) * 2.0f;
}

