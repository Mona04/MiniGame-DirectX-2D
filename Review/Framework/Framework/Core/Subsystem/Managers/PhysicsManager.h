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
	void AcquireMonsters();

private:
	void Update_by_Blocks(class RigidBody* other);
	void Update_by_UnMovable(class RigidBody* other, class BoundBox& unMovable);
	void Update_Movable_by_Character(class RigidBody* other, class RigidBody* unMovable);
	void Update_Movable_by_Movable(class RigidBody* other, class RigidBody* unMovable);
	void Update_Character_by_Movable(class RigidBody* other, class RigidBody* unMovable);
	void Update_Character_by_Effect_for_Attack(class Actor* other, class Actor* effect);
	void Update_Character_by_Effect_for_Dropped_Item(class Actor* other, class Actor* effect);
	void Update_Character_by_Effect(class Actor* other, class Actor* effect);

public:
	ScannedResult ScanField(const Vector3& pos, const Vector3& scale, const int& direct);

private:
	class Timer* timer;
	class Input* input;
	class DataManager* dataManager;
	class SceneManager* sceneManager;
	class MonsterManager* monsterManager;

	Vector3 _gravity;

	std::vector<class RigidBody*> _unMovables;
	std::vector<class RigidBody*> _movables;
	std::vector<BlockKind> data_blocks;
	std::vector<class BoundBox> _blocks;
	std::vector<class RigidBody*> _characterRigidBodies;
	std::vector<class Actor*> _characters;
	std::vector<class Actor*> _effects;

	int _width;
	int _height;
};