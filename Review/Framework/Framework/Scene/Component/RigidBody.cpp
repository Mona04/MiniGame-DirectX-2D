#include "Framework.h"
#include "RigidBody.h"

#define MOVE_LIMIT Vector3(25, 25, 0)

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

	_moveVector += var;
	OffGroundFlag(GroundFlag::GroundFlag_Bottom);
}

void RigidBody::Move(const Vector3& var)
{
	_moveVector += var;

	if (IsOnGroundFlag(GroundFlag::GroundFlag_Left) && _moveVector.x < 0)
		_moveVector.x = 0;
	if (IsOnGroundFlag(GroundFlag::GroundFlag_Right) && _moveVector.x > 0)
		_moveVector.x = 0;

	if (_moveVector.x < _limit_min.x)
		_moveVector.x = _limit_min.x;
	if (_moveVector.x > _limit_max.x)
		_moveVector.x = _limit_max.x;
	if (_moveVector.y < _limit_min.y)
		_moveVector.y = _limit_min.y;
	if (_moveVector.y > _limit_max.y)
		_moveVector.y = _limit_max.y;
}

void RigidBody::KnockBack(const Vector3& var)
{
	_moveVector += var;

	if (IsOnGroundFlag(GroundFlag::GroundFlag_Left) && _moveVector.x < 0)
		_moveVector.x = 0;
	if (IsOnGroundFlag(GroundFlag::GroundFlag_Right) && _moveVector.x > 0)
		_moveVector.x = 0;
}

void RigidBody::AddMoveVector(const Vector3& var)
{
	_moveVector += var;
	if (_moveVector.y > 0)
		_moveVector.y = _moveVector.y > MOVE_LIMIT.y ? MOVE_LIMIT.y : _moveVector.y + var.y;
	else if (_moveVector.y < 0)
		_moveVector.y = _moveVector.y < -MOVE_LIMIT.y ? -MOVE_LIMIT.y : _moveVector.y + var.y;
}

void RigidBody::AddMoveVector_Limited(const Vector3& var)
{
	_moveVector += var;
	if (_moveVector.y > 0)
		_moveVector.y = _moveVector.y > _limit_max.y ? _limit_max.y : _moveVector.y + var.y;
	else if (_moveVector.y < 0)
		_moveVector.y = _moveVector.y < _limit_min.y ? _limit_min.y : _moveVector.y + var.y;
}

