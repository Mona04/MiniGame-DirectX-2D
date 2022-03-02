#pragma once
#include "IComponent.h"

enum class RigidBodyType : uint
{
	unMovable,  // 고정지형
	Movable,  // 움직일 지형
	Character,  // 캐릭터
	Overlap,
};

enum GroundFlag : ulong
{
	GroundFlag_Left = 1UL << 0,
	GroundFlag_Right = 1UL << 1,
	GroundFlag_Top = 1UL << 2,
	GroundFlag_Bottom = 1UL << 3
};

class RigidBody final : public IComponent
{
private:
	friend class PhysicsManager;
public:
	RigidBody(class Context* context);
	~RigidBody() = default;

	void Update() override;
	void Render() override;

	void SetBoundBoxAndTransform(class Transform* transform);
	void Translate() { transform->SetPosition(_boundBox.GetCenter(transform)); }
	void Translate_Tmp(const Vector3& var) { _boundBox.Translate(var); }  // moveVector 바꾸고 이거 하고 바로 위에거 순서

	void Jump(const Vector3& var);
	void Move(const Vector3& var);

public:
	const RigidBodyType& GetRigidBodyType() { return _rigidBodyType; }
	void SetRigidBodyType(const RigidBodyType& type) { _rigidBodyType = type; }

	const float GetLeft() { return transform->GetPosition().x - transform->GetScale().x / 2; }
	const float GetRight() { return transform->GetPosition().x + transform->GetScale().x / 2; }
	const float GetBottom() { return transform->GetPosition().y - transform->GetScale().y / 2; }
	const float GetTop() { return transform->GetPosition().y + transform->GetScale().y / 2; }

	const Vector3& GetMoveVector() { return _moveVector; }
	void SetMoveVector(const Vector3& var) { _moveVector = var; }
	void AddMoveVector(const Vector3& var);
	void AddMoveVector_Limited(const Vector3& var);
	void AddMoveVectorFloat(const float x, const float y) { _moveVector += Vector3(x, y, 0); }

	const Vector3& GetVelocity() { return _velocity; }
	void SetVelocity(const Vector3& var) { _velocity = var; }
	void AddVelocity(const Vector3& var);

	const float& GetMass() { return _mass; }
	void SetMass(const float& var) { _mass = var; }

	const float& GetFriction() { return _friction; }
	void SetFriction(const float& var) { _friction = var; }

	Transform* GetTransform() const { return transform; }

	BoundBox& GetBoundBox() { return _boundBox; }

	const Vector3& GetMinLimit() { return _limit_min; }
	void SetMinLimit(const Vector3& var) { _limit_min = var; }

	const Vector3& GetMaxLimit() { return _limit_max; }
	void SetMaxLimit(const Vector3& var) { _limit_max = var; }

	ulong GetGroundFlag() { return groundFlag; }
	void SetGroundFlag(const ulong& var) { groundFlag = var; }
	void OnGroundFlag(const GroundFlag& var) { groundFlag |= var; }
	void OffGroundFlag(const GroundFlag& var) { groundFlag &= ~var; }
	const bool IsOnGroundFlag(const GroundFlag& var) { return (groundFlag & var) > 0UL; }

private:
	RigidBodyType _rigidBodyType;
	Transform* transform;

	Vector3 _moveVector;  // 매 Tick 마다 0으로 초기화 되는 값
	Vector3 _velocity;    // 충돌이 아니면 0으로 초기화 되지 않는 값
	float _mass;
	float _friction;
	BoundBox _boundBox;

	Vector3 _limit_min = Vector3(-10.0f, -10.0f, 0.0f);
	Vector3 _limit_max = Vector3(+10.0f, +10.0f, 0.0f);
	ulong groundFlag;
};