#pragma once
#include "../ISubsystem.h"

enum class MonsterEffectType : uint
{
	LevelUp,
	Dropped_Item,
	Skill_Effect
};

class MonsterManager final : public ISubsystem
{
public:
	MonsterManager(class Context* context);
	~MonsterManager();

	const bool Initialize() override;
	void Update();

	void Clear();
	void Clear_();
	void Clear_Monsters();

public:
	void ToggleEvolution();
	void UpdateEvolutionData();

	void Spawn(const std::string& path, const struct SpawnInfo& info, const int& team);
	void SpawnAuto(const std::string& name, int team, bool isAgressive);
	void SetSpawnList(class Data_Spawn* data, int team = 1);
	std::vector<class Actor*>& GetMonsters() { return monsters; }
	
	void Load_LevelUp_Effect(class Controller* controller);
	void Load_Dropped_Item(class Data_Item* data, const Vector3& pos);
	void Load_Skill_Effect(Actor& actor, Data_Skill* data, bool direct, const AnimationMotionType& type = AnimationMotionType::Stand);

	void Teleport(const std::string& sceneName, const std::string& actorName, const Vector3& pos);

private:
	void Init_Common_Actors();
	void Init_HP_Gauges();

	void Update_Monsters();
	void Update_MonsterHP();
	void Update_LevelUpEffect();
	void Update_Dropped_Item();
	void Update_SkillEffect();

	void Resize_Skill_Effect();
	
public:
	class VertexBuffer* GetHPBarInstanceBuffer_Frame() { return hp_Bar_InstanceBuffer_Frame; }
	class VertexBuffer* GetHPBarInstanceBuffer_Gauge() { return hp_Bar_InstanceBuffer_Gauge; }
	class ProgressBar* GetHP_Bar() { return hp_Bar; }
	void SetHP_Bar(class ProgressBar* var);

	std::map<MonsterEffectType, std::vector<Actor*>> GetEffectsMap() { return effects_map; }
	std::vector<Actor*>& GetEffects(const MonsterEffectType& type) { return effects_map[type]; }

private:
	class SceneManager* sceneManager;
	class UIManager* uiManager;
	class DataManager* dataManager;
	class Thread* thread;

	std::map<MonsterEffectType, std::vector<Actor*>> effects_map;

	class ProgressBar* hp_Bar = nullptr;
	class VertexBuffer* hp_Bar_InstanceBuffer_Frame;
	class VertexBuffer* hp_Bar_InstanceBuffer_Gauge;
	class Geometry<struct VertexPositionScaleSprite>* hp_Bar_Geometry_Frame;
	class Geometry<struct VertexPositionScaleSprite>* hp_Bar_Geometry_Gauge;

	std::vector<class Actor*> monsters;

	class Evolution* evolution = nullptr;
}; 