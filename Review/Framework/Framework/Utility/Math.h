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
	static const float ToRadian(const float& degree) { return degree * TO_RAD; }
	static const float ToDegree(const float& radian) { return radian * TO_DEG; }

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
	static const T Clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : value > max ? max : value;
	}

	template <typename T>
	static const T Abs(const T& value)
	{
		return value >= 0 ? value : -value;
	}
	
	template<typename T>
	static const int RoundDown(const T& value)
	{
		return (int)value > value ? (int)value - 1 : (int)value;
	}

	template <typename T>
	static const T Max(const T& lhs, const T& rhs)
	{
		return lhs > rhs ? lhs : rhs;
	}

	template <typename T>
	static const T Min(const T& lhs, const T& rhs)
	{
		return lhs < rhs ? lhs : rhs;
	}

	template <typename T>
	static const int Sign(const T& value)
	{
		return (T(0) < value) - (T(0) > value);
	}

	template <typename T>
	static const bool Equals(const T& lhs, const T& rhs, const T& e = std::numeric_limits<T>::epsilon())
	{
		return lhs + e >= rhs && lhs - e <= rhs;
	}

	static const Vector3 Distance(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(sqrt((lhs.x - rhs.x) * (lhs.x - rhs.x)), 
			sqrt((lhs.y - rhs.y) * (lhs.y - rhs.y)), sqrt((lhs.z - rhs.z) * (lhs.z - rhs.z)));
	}

	static const Vector3 QuaternionToEuler(const Quaternion& qut)
	{
		Vector3 output;
		float x = qut.x;
		float y = qut.y;
		float z = qut.z;
		float w = qut.w;

		double test = x * y + z * w;
		if (test > 0.499f) { // singularity at north pole  
			output.y = 2 * atan2f(x, w);
			output.z = PI_DIV_2;
			output.x = 0;
		}
		else if (test < -0.499f) { // singularity at south pole  
			output.y = -2 * atan2(x, w);
			output.z = -PI_DIV_2;
			output.x = 0;
		}
		else
		{
			float sqx = x * x;
			float sqy = y * y;
			float sqz = z * z;
			output.y = atan2f(2 * y * w - 2 * x * z, 1 - 2 * sqy - 2 * sqz);
			output.z = asinf(2 * test);
			output.x = atan2f(2 * x * w - 2 * y * z, 1 - 2 * sqx - 2 * sqz);
		}

		return output * TO_DEG;
	}

	static const Quaternion EulerToQuaternion(const Vector3& euler)
	{
		Quaternion quat;

		float x = euler.x * Math::TO_RAD;
		float y = euler.y * Math::TO_RAD;
		float z = euler.z * Math::TO_RAD;

		float cx = std::cos(x / 2);
		float sx = std::sin(x / 2);
		float cy = std::cos(y / 2);
		float sy = std::sin(y / 2);
		float cz = std::cos(z / 2);
		float sz = std::sin(z / 2);

		quat.x = sx * cy * cz - cx * sy * sz;
		quat.y = cx * sy * cz + sx * cy * sz;
		quat.z = cx * cy * sz - sx * sy * cz;
		quat.w = cx * cy * cz + sx * sy * sz;

		return quat;
	}

	static const Vector3 MatrixToScale(const Matrix& matrix)
	{
		int sign_x = Math::Sign(matrix._11 * matrix._12 * matrix._13 * matrix._14) < 0 ? -1 : 1;   // 이거 없어서 털림
		int sign_y = Math::Sign(matrix._21 * matrix._22 * matrix._23 * matrix._24) < 0 ? -1 : 1;
		int sign_z = Math::Sign(matrix._31 * matrix._32 * matrix._33 * matrix._34) < 0 ? -1 : 1;

		return Vector3
		(
			static_cast<float>(sign_x) * sqrtf(powf(matrix._11, 2) + powf(matrix._12, 2) + powf(matrix._13, 2)),
			static_cast<float>(sign_y) * sqrtf(powf(matrix._21, 2) + powf(matrix._22, 2) + powf(matrix._23, 2)),
			static_cast<float>(sign_z) * sqrtf(powf(matrix._31, 2) + powf(matrix._32, 2) + powf(matrix._33, 2))
		);
	}

	static const Quaternion MatrixToQuaternion(const Matrix& matrix)
	{
		Quaternion quaternion;

		float sq;
		float half;
		float scale = matrix._11 + matrix._22 + matrix._33;

		if (scale > 0.0f)
		{
			sq = sqrt(scale + 1.0f);
			quaternion.w = sq * 0.5f;
			sq = 0.5f / sq;

			quaternion.x = (matrix._23 - matrix._32) * sq;
			quaternion.y = (matrix._31 - matrix._13) * sq;
			quaternion.z = (matrix._12 - matrix._21) * sq;

			return quaternion;
		}
		if ((matrix._11 >= matrix._22) && (matrix._11 >= matrix._33))
		{
			sq = sqrt(1.0f + matrix._11 - matrix._22 - matrix._33);
			half = 0.5f / sq;

			quaternion.x = 0.5f * sq;
			quaternion.y = (matrix._12 + matrix._21) * half;
			quaternion.z = (matrix._13 + matrix._31) * half;
			quaternion.w = (matrix._23 - matrix._32) * half;

			return quaternion;
		}
		if (matrix._22 > matrix._33)
		{
			sq = sqrt(1.0f + matrix._22 - matrix._11 - matrix._33);
			half = 0.5f / sq;

			quaternion.x = (matrix._21 + matrix._12) * half;
			quaternion.y = 0.5f * sq;
			quaternion.z = (matrix._32 + matrix._23) * half;
			quaternion.w = (matrix._31 - matrix._13) * half;

			return quaternion;
		}
		sq = sqrt(1.0f + matrix._33 - matrix._11 - matrix._22);
		half = 0.5f / sq;

		quaternion.x = (matrix._31 + matrix._13) * half;
		quaternion.y = (matrix._32 + matrix._23) * half;
		quaternion.z = 0.5f * sq;
		quaternion.w = (matrix._12 - matrix._21) * half;

		return quaternion;
	}
};