#include "Framework.h"
#include "RigidBody.h"

#define MOVE_LIMIT Vector3(20, 20, 0)

RigidBody::RigidBody(Context* context)
	: IComponent(context)
	, transform(nullptr)
	, _moveVector(Vector3(0, 0, 0))
	, _rigidBodyType(RigidBodyType::Character)
{
	type = ComponentType::RigidBody;
	_boundBox.maxPoint = Vector3(5, 5, 5);
	_boundBox.minPoint = Vector3(0, 0, 0);
}

void RigidBody::Update()
{
}

void RigidBody::Render()
{
}

void RigidBody::SetBoundBoxAndTransform(Transform* transform)
{
	this->transform = transform;
}

void RigidBody::Jump(const Vector3& var)
{
	if (!IsOnGroundFlag(GroundFlag::GroundFlag_Bottom))
		return;

	_velocity.y = var.y;
	OffGroundFlag(GroundFlag::GroundFlag_Bottom);
}

void RigidBody::Move(const Vector3& var)
{
	_moveVector += var;
	_velocity.x = 0.f;

	if (var.y != 0) {
		if (_moveVector.y < _limit_min.y)
			_moveVector.y = _limit_min.y;
		if (_moveVector.y > _limit_max.y)
			_moveVector.y = _limit_max.y;
	}
	if (var.x != 0) {
		if (_moveVector.x < _limit_min.x)
			_moveVector.x = _limit_min.x;
		if (_moveVector.x > _limit_max.x)
			_moveVector.x = _limit_max.x;
	}
}

void RigidBody::AddMoveVector(const Vector3& var)
{
	_moveVector += var;
	_moveVector.y = Math::Clamp(_moveVector.y, -MOVE_LIMIT.y, MOVE_LIMIT.y);
}

void RigidBody::AddMoveVector_Limited(const Vector3& var)
{
	_moveVector += var;
	_moveVector.y = Math::Clamp(_moveVector.y, _limit_min.y, _limit_max.y);
}

void RigidBody::AddVelocity(const Vector3& var)
{
	_velocity += var;
	_velocity.y = Math::Clamp(_velocity.y, -MOVE_LIMIT.y, MOVE_LIMIT.y);
}

