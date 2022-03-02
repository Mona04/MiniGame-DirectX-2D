#pragma once
#include "../ISubsystem.h"

enum class ScannedResult : uint
{
	Flat = 0u,
	Wall = 1u,
	Stair_Upper = 2u,
	Cliff = 3u,
	Stair_Lower = 4u
};

class PhysicsManager final : public ISubsystem
{
public:
	PhysicsManager(class Context* context);
	~PhysicsManager();

	void Clear();

	const bool Initialize() override;
	void Update();

	void AddActor(class Actor* actor);
	void AcquireScene(class Scene* scene);
	void ChangeRigidBodyType(class RigidBody* rb, int type);

private:
	void Update_Process();
	void Update_Gravity(class RigidBody* other);
	void Update_by_Blocks(class RigidBody* other, bool bUpdown = true);
	void Update_by_UnMovable(class RigidBody* other, class BoundBox& unMovable, bool bUpdown = true);
	void Update_Movable_by_Character(class RigidBody* other, class RigidBody* unMovable);
	void Update_Movable_by_Movable(class RigidBody* other, class RigidBody* unMovable);
	void Update_Character_by_Movable(class RigidBody* other, class RigidBody* unMovable);
	void Update_Character_by_Effect_for_Attack(class Actor* other, class Actor* effect);

public:
	ScannedResult ScanField(const Vector3& pos, const Vector3& scale, const int& direct);
	std::vector<class Actor*> TraceByOverlapped(class Actor* other) { return TraceByVectors(other, _overlappeds); }
	std::vector<class Actor*> TraceByVectors(class Actor* other, std::vector<class Actor*> in);
	std::vector<class Actor*> TraceByVectors(class Actor* other, std::vector<class RigidBody*> in);

private:
	class Timer* timer;
	class Input* input;
	class DataManager* dataManager;
	class SceneManager* sceneManager;
	class MonsterManager* monsterManager;

	const Vector3 _gravity;
	const float _step = 60.f;
	const float _delta = 1000.f / _step / 22.f;

	std::vector<class RigidBody*> _unMovables;
	std::vector<class RigidBody*> _movables;
	std::vector<BlockKind> data_blocks;
	std::vector<class BoundBox> _blocks;
	std::vector<class RigidBody*> _overlappeds;
	std::vector<class RigidBody*> _characters;

	int _width;
	int _height;
};