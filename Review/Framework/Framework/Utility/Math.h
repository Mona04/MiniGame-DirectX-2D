#pragma once
#include "Framework.h"
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Vector3.h"
#include "Framework/Math/Matrix.h"
#include "Framework/Math/Quaternion.h"
#include <random>

class Math final
{
public:
	static constexpr float PI = 3.14159265359f;
	static constexpr float PI_2 = 6.28318530718f;
	static constexpr float PI_DIV_2 = 1.57079632679f;
	static constexpr float PI_DIV_4 = 0.78539816339f;
	static constexpr float TO_DEG = 180.0f / PI;
	static constexpr float TO_RAD = PI / 180.0f;

public:
	static const float ToRadian(float degree) { return degree * TO_RAD; }
	static const float ToDegree(float radian) { return radian * TO_DEG; }

	static const int Random(const int& min, const int& max)
	{
		if (max <= min) return 0;

		static std::random_device rn;
		static std::mt19937_64 rnd(rn());

		std::uniform_int_distribution<int> range(min, max - 1);
		return range(rnd);
	}

	static bool Gambling(const float& percentage)
	{
		static std::random_device rn;
		static std::mt19937_64 rnd(rn());

		std::uniform_int_distribution<int> range(0, 100);
		return range(rnd) < (int)(percentage * 100.0f);
	}

	template <typename T>
	static T Clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : value > max ? max : value;
	}

	template <typename T>
	static T Lerp(float alpha, const T& from, const T& to)
	{
		float norm_alpha = Clamp(alpha, 0.f, 1.f);
		return to * norm_alpha + from * (1 - norm_alpha);
	}

	template <typename T>
	static T Abs(const T& value)
	{
		return value >= 0 ? value : -value;
	}
	
	template<typename T>
	static int RoundDown(const T& value)
	{
		return (int)value > value ? (int)value - 1 : (int)value;
	}

	template <typename T>
	static T Max(const T& lhs, const T& rhs)
	{
		return lhs > rhs ? lhs : rhs;
	}

	template <typename T>
	static T Min(const T& lhs, const T& rhs)
	{
		return lhs < rhs ? lhs : rhs;
	}

	template <typename T>
	static int Sign(const T& value)
	{
		return (T(0) < value) - (T(0) > value);
	}

	template <typename T>
	static bool Equals(const T& lhs, const T& rhs, const T& e = std::numeric_limits<T>::epsilon())
	{
		return lhs + e >= rhs && lhs - e <= rhs;
	}

	static Vector3 Distance(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(sqrt((lhs.x - rhs.x) * (lhs.x - rhs.x)), 
			sqrt((lhs.y - rhs.y) * (lhs.y - rhs.y)), sqrt((lhs.z - rhs.z) * (lhs.z - rhs.z)));
	}

	static Vector3 QuaternionToEuler(const Quaternion& q)
	{
		// Derivation from http://www.geometrictools.com/Documentation/EulerAngles.pdf
		float check = 2.0f * (q.x * q.y + q.w * q.z);

		if (check < -0.999995f)
		{
			return Vector3
			(
				atan2f(2.0f * (q.x * q.w - q.y * q.z), 1.0f - 2.0f * (q.x * q.x + q.z * q.z)) * 180 / Math::PI,
				0,
				-90
			);
		}

		if (check > 0.999995f)
		{
			return Vector3
			(
				atan2f(2.0f * (q.x * q.w - q.y * q.z), 1.0f - 2.0f * (q.x * q.x + q.z * q.z)) * 180 / Math::PI,
				0,
				90
			);
		}

		return Vector3
		(
			atan2f(2.0f * (q.x * q.w - q.y * q.z), 1.0f - 2.0f * (q.x * q.x + q.z * q.z)) * 180 / Math::PI,
			atan2f(2.0f * (q.y * q.w - q.x * q.z), 1.0f - 2.0f * (q.y * q.y + q.z * q.z)) * 180 / Math::PI,
			asinf(check) * 180 / Math::PI
		);
	}

	static const Quaternion EulerToQuaternion(const Vector3& euler)
	{
		double halfRoll  = Math::ToRadian(euler.x) * 0.5;
		double halfPitch = Math::ToRadian(euler.y) * 0.5;
		double halfYaw   = Math::ToRadian(euler.z) * 0.5;

		double sinRoll = sin(halfRoll);
		double cosRoll = cos(halfRoll);
		double sinPitch = sin(halfPitch);
		double cosPitch = cos(halfPitch);
		double sinYaw = sin(halfYaw);
		double cosYaw = cos(halfYaw);

		Quaternion ret = Quaternion
		(
			(+cosPitch * cosYaw * sinRoll + sinPitch * sinYaw * cosRoll),
			(+cosPitch * sinYaw * sinRoll + sinPitch * cosYaw * cosRoll),
			(-sinPitch * cosYaw * sinRoll + cosPitch * sinYaw * cosRoll),
			(+cosPitch * cosYaw * cosRoll - sinPitch * sinYaw * sinRoll)
		);
		//ret.Normalize();
		return ret;
	}

	static const Vector3 MatrixToScale(const Matrix& matrix)
	{
		//int sign_x = Math::Sign(matrix._11 * matrix._12 * matrix._13 * matrix._14) < 0 ? -1 : 1;   // 이거 없어서 털림
		//int sign_y = Math::Sign(matrix._21 * matrix._22 * matrix._23 * matrix._24) < 0 ? -1 : 1;
		//int sign_z = Math::Sign(matrix._31 * matrix._32 * matrix._33 * matrix._34) < 0 ? -1 : 1;

		return Vector3
		(
			sqrtf(powf(matrix._11, 2) + powf(matrix._12, 2) + powf(matrix._13, 2)),
			sqrtf(powf(matrix._21, 2) + powf(matrix._22, 2) + powf(matrix._23, 2)),
			1
		);
	}

	static const Quaternion MatrixToQuaternion(const Matrix& matrix)
	{
		Quaternion quaternion;
		Vector3 scale = MatrixToScale(matrix);

		float m11 = matrix._11 / scale.x;
		float m12 = matrix._21 / scale.y;
		float m13 = matrix._31 / scale.z;
		float m21 = matrix._12 / scale.x;
		float m22 = matrix._22 / scale.y;
		float m23 = matrix._32 / scale.z;
		float m31 = matrix._13 / scale.x;
		float m32 = matrix._23 / scale.y;
		float m33 = matrix._33 / scale.z;

		float sq;
		float tr = m11 + m22 + m33;

		if (tr > -1.0f)  // tr + 1 >= 0 => w 구함
		{
			sq = sqrt(tr + 1.0f);
			quaternion.w = sq * 0.5f;

			quaternion.x = (m32 - m23) / (4 * quaternion.w);
			quaternion.y = (m13 - m31) / (4 * quaternion.w);
			quaternion.z = (m21 - m12) / (4 * quaternion.w);

			return quaternion;
		}
		else if (m11 > m22 && m11 > m33)  // x 구함
		{
			sq = sqrt(1.0f + m11 - m22 - m33);
			quaternion.x = sq * 0.5f;

			quaternion.y = (m12 + m21) / (4 * quaternion.x);
			quaternion.z = (m13 + m31) / (4 * quaternion.x);
			quaternion.w = (m32 - m32) / (4 * quaternion.x);

			return quaternion;
		}
		if (m22 > m11 && m22 > m33)  // y 구함
		{
			sq = sqrt(1.0f + m22 - m11 - m33);
			quaternion.y = sq * 0.5f;

			quaternion.x = (m21 + m12) / (4 * quaternion.y);
			quaternion.z = (m32 + m23) / (4 * quaternion.y);
			quaternion.w = (m32 - m23) / (4 * quaternion.y);

			return quaternion;
		}
		else
		{
			sq = sqrt(1.0f + m33 - m11 - m22);   // z 구함
			quaternion.z = sq * 0.5f;

			quaternion.x = (m31 + m13) / (4 * quaternion.z);
			quaternion.y = (m32 + m23) / (4 * quaternion.z);
			quaternion.w = (m21 - m12) / (4 * quaternion.z);

			return quaternion;
		}
	}
};