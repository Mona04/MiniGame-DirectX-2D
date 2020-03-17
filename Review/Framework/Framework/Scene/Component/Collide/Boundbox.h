#pragma once

enum class Intersection : uint
{
	Outside,
	Inside,
	Intersect
};

class BoundBox final
{
public:
	BoundBox();
	BoundBox(const Vector3& min, const Vector3& max);
	BoundBox(const std::vector<struct VertexTexture>& vertices);
	BoundBox(const class Transform* transform); // For UI
	~BoundBox() = default;

	void Init(const class Transform* transform);
	void Init(const Vector3& min, const Vector3& max);
	
	const Vector3 GetCenter() const { return (maxPoint + minPoint) * 0.5f; }
	const Vector3 GetCenter(Transform* transform);
	void SetCenter(const Vector3& var) { Vector3 dist = var - GetCenter(); minPoint += dist; maxPoint += dist; }

	const Vector3 GetSize() const { return maxPoint - minPoint; }
	void SetSize(const Vector3& var) { Vector3 center = GetCenter(); minPoint = center - var / 2.0f; maxPoint = center + var / 2.0f; }
	const Vector3 GetExtents() const { return GetSize() * 0.5f; }
	
	const float GetLeft() { return minPoint.x; }
	const float GetRight() { return maxPoint.x; }
	const float GetBottom() { return minPoint.y; }
	const float GetTop() { return maxPoint.y; }

	const Intersection IsInside(const Vector3& point);
	const Intersection IsInside(const BoundBox& box);

	const BoundBox Transformed(const Matrix& transform);
	BoundBox& Translate(const Vector3& var);

public:
	Vector3 minPoint;
	Vector3 maxPoint;

	Vector3 offset;
};