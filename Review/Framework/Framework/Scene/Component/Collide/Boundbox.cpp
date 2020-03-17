#include "Framework.h"
#include "BoundBox.h"

#undef min
#undef max

BoundBox::BoundBox()
{
	minPoint = Vector3
	(
		std::numeric_limits<float>::max(),
		std::numeric_limits<float>::max(),
		std::numeric_limits<float>::max()
	);

	maxPoint = Vector3
	(
		std::numeric_limits<float>::min(),
		std::numeric_limits<float>::min(),
		std::numeric_limits<float>::min()
	);
}

BoundBox::BoundBox(const Vector3 & min, const Vector3 & max)
	: minPoint(min)
	, maxPoint(max)
{
}

BoundBox::BoundBox(const std::vector<VertexTexture>& vertices)
{
	minPoint = Vector3
	(
		std::numeric_limits<float>::max(),
		std::numeric_limits<float>::max(),
		std::numeric_limits<float>::max()
	);

	maxPoint = Vector3
	(
		std::numeric_limits<float>::min(),
		std::numeric_limits<float>::min(),
		std::numeric_limits<float>::min()
	);

	for (auto& vertex : vertices)
	{
		minPoint.x = Math::Min(minPoint.x, vertex.position.x);
		minPoint.y = Math::Min(minPoint.y, vertex.position.y);
		minPoint.z = Math::Min(minPoint.z, vertex.position.z);

		maxPoint.x = Math::Max(maxPoint.x, vertex.position.x);
		maxPoint.y = Math::Max(maxPoint.y, vertex.position.y);
		maxPoint.z = Math::Max(maxPoint.z, vertex.position.z);
	}
}

BoundBox::BoundBox(const Transform* transform)
{
	Vector3 leftTop = transform->GetPosition();
	Vector3 scale = transform->GetScale();
	minPoint = leftTop;
	minPoint.y -= scale.y;
	maxPoint = leftTop;
	maxPoint.x += scale.x;
}

void BoundBox::Init(const Transform* transform)
{
	if (!transform)
		return;

	Vector3 dist = (GetSize() - transform->GetScale()) / 2.0f;
	offset.x = -dist.x;
	offset.y = dist.y;
	offset.z = 0;
	minPoint = Vector3(0.0f, 0.0f, 0.0f);
	maxPoint = transform->GetScale();
	SetCenter(transform->GetPosition() + offset);
}

void BoundBox::Init(const Vector3& min, const Vector3& max)
{
	minPoint = min;
	maxPoint = max;
	offset = Vector3(0.0f, 0.0f, 0.0f);
}

const Vector3 BoundBox::GetCenter(Transform* transform)
{
	return GetCenter() - offset;
}

const Intersection BoundBox::IsInside(const Vector3 & point)
{
	if (
		point.x < minPoint.x || point.x > maxPoint.x ||
		point.y < minPoint.y || point.y > maxPoint.y )
		return Intersection::Outside;

	return Intersection::Inside;
}

const Intersection BoundBox::IsInside(const BoundBox & box)
{
	if (
		box.maxPoint.x < minPoint.x || box.minPoint.x > maxPoint.x ||
		box.maxPoint.y < minPoint.y || box.minPoint.y > maxPoint.y)
		return Intersection::Outside;
	else if (
		box.minPoint.x < minPoint.x || box.maxPoint.x > maxPoint.x ||
		box.minPoint.y < minPoint.y || box.maxPoint.y > maxPoint.y )
		return Intersection::Intersect;
	else
		return Intersection::Inside;
}

const BoundBox BoundBox::Transformed(const Matrix & transform)
{
	Vector3 newCenter;
	newCenter = Vector3::TransformCoord(GetCenter(), transform);
	//D3DXVec3TransformCoord(&newCenter, &GetCenter(), &transform);
	Vector3 oldEdge = GetExtents();
	Vector3 newEdge = Vector3
	(
		Math::Abs(transform._11) * oldEdge.x + Math::Abs(transform._21) * oldEdge.y + Math::Abs(transform._31) * oldEdge.z,
		Math::Abs(transform._12) * oldEdge.x + Math::Abs(transform._22) * oldEdge.y + Math::Abs(transform._32) * oldEdge.z,
		Math::Abs(transform._13) * oldEdge.x + Math::Abs(transform._23) * oldEdge.y + Math::Abs(transform._33) * oldEdge.z
	);

	return BoundBox(newCenter - newEdge, newCenter + newEdge);
}

BoundBox& BoundBox::Translate(const Vector3& var)
{
	minPoint += var;
	maxPoint += var;

	return *this;
}
