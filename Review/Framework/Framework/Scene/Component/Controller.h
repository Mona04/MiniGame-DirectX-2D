#pragma once
#include "IComponent.h"

class Controller : public IComponent
{
public:
	Controller(class Context* context);
	~Controller();

	void Update() override;
	void Render() override {};

	void SetActor(class Actor* actor);

	void Stand();
	void Walk(const int& direct);
	void Run(const int& direct);
	void Jump();
	void Gaurd();
	void Attack1();
	void Attack2();
	void Hit(Data_Skill* data, Controller* attacker, const Vector3& knockBack, const float& damageFactor = 1.0f);
	void Die();
	
	void SuperJump(const int& factor);
	void Heal(const int& hp_var, const int& mp_var, const int& sp_var);
	void Resurrection();

	void Portal();
	void Teleport(const Vector3& pos);
	void Dialog();
	
	void Evolution(const std::string& name);
	void LevelUp();
	void ObtainExp(const int& exp);

	void RandomSkillChange();
	void RandomRGBChange();

	void ChangeMobData(const std::string& name);
	void ChangeScale(const Vector3& scale);

	void RandomAttack(float time, float percent1, float percent2, float percent3);
	void RandomWalk(float time);
	void RandomRun(float time);

	bool IsHostile() { return isHostile; }
	bool IsDied() { return isDied; }

public:
	bool Tuning();
	bool CalcConsumed(Data_Skill* skill);
	int CalcDamage(const float& damage_fire, const float& damage_water, const float& damage_light, const float& damage_dark, const float& damageFactor);
	void MoveAuto(const int& isWalk = 0);
	bool AttackAuto(const int& type = 1);

	void MakeReverce() { this->direct = direct == 0 ? 1 : 0; }

	bool IsInvincible() { return isInvincible; }
	const int& GetDirect() { return this->direct; }
	void SetDirect(const int& var) { this->direct = var; }
	void SetInteraction(Actor* actor) { targetActor = actor; }

	RigidBody* GetRigidBody() { return rigidBody; }

	Actor* GetActor() { return this->actor; }
	void SetEffectActor(Actor* actor) { effectActor = actor; }
	Actor* GetEffectActor() { return effectActor; }
	void SetParentActor(Actor* actor) { parentActor = actor; }
	Actor* GetParentActor() { return parentActor; }
	void SetAttackActor(Actor* actor) { attackActor = actor; isHostile = true; }

	void SetTeam(const int& var) { team = var; }
	const int& GetTeam() { return team; }
	void SetActType(const int& var) { actType = var; }
	const int& GetActType() { return actType; }

	Vector3 GetScale() { return transform->GetScale(); }

public:
	void SetHitRange(const Vector3& var) { _hitRange = var; }
	const Vector3& GetHitRange() { return _hitRange; }
	const Vector3& GetAttack1Range() { return _attack1Range; }
	const Vector3& GetAttack2Range() { return _attack2Range; }

	const int GetMaxHP()  { return data_mob->_maxHp * (int)(GetLVFactor()); }
	const int GetHP()     { return this->hp; }
	const int GetMaxMP()  { return data_mob->_maxMp * (int)(GetLVFactor()); }
	const int GetMP()     { return this->mp; }
	const int GetMaxSP()  { return data_mob->_maxSp * (int)(GetLVFactor()); }
	const int GetSP()     { return this->sp; }
	const int GetMaxExp() { return this->lv > (data_mob->_defaultLv + 10) ? data_mob->_maxExp * (int)GetLVFactor() * 10 : data_mob->_maxExp * GetLVFactor(); }
	const int GetExp()    { return this->exp; }
	void TmpGauge()       { hp = 100; mp = 100; sp = 100; }

	const int GetLv() { return this->lv; }
	void SetLv(const int& var) { this->lv = var; }
	const float GetLVFactor();

	void SetJumpFactor(const float& var);
	const float& GetJumpFactor() { return _jumpFactor; }
	void SetSpeedFactor(const float& var);
	const float& GetSpeedFactor() { return _speedFactor; }

	const bool& IsSuperArmor() { return isSuperArmor; }
	void SetSuperArmor(const bool& var) { isSuperArmor = var; }

	void SetProtagonist(const bool& var) { isProtagonist = var; }

	void SetMobData(Data_Mob* data);
	Data_Mob* GetMobData() { return data_mob; }
	
	void SetAttack1Data(Data_Skill* data);
	Data_Skill* GetAttack1Data() { return data_attack1; }
	
	void SetAttack2Data(Data_Skill* data);
	Data_Skill* GetAttack2Data() { return data_attack2; }
	
	void SetGuardData(Data_Skill* data) { this->data_guard = data; }
	Data_Skill* GetGuardData() { return data_guard; }

	void SetPortalData(Data_Portal* data) { this->data_portal = data; }
	Data_Portal* GetPortalData() { return data_portal; }

	void SetDialogData(Data_Dialog* data) { this->data_dialog = data; }
	Data_Dialog* GetDialogData() { return data_dialog; }

	void SetItemData(Data_Item* data) { this->data_item = data; }
	Data_Item* GetItemData() { return data_item; }

private:
	Timer* timer;
	SceneManager* sceneManager;
	MonsterManager* monsterManager;
	DialogManager* dialogManager;
	DataManager* dataManager;
	UIManager* uiManager;
	PhysicsManager* physcisManager;
	ResourceManager* resourceManager;
	GameManager* gameManager;

	Actor* actor;
	Renderable* renderable;
	Transform* transform;
	RigidBody* rigidBody;
	Animator* animator;

	Data_Mob* data_mob = nullptr;
	Data_Skill* data_attack1 = nullptr;
	Data_Skill* data_attack2 = nullptr;
	Data_Skill* data_guard = nullptr;
	Data_Portal* data_portal = nullptr;
	Data_Dialog* data_dialog = nullptr;
	Data_Item* data_item = nullptr;

	Actor* attackActor = nullptr;
	Actor* targetActor = nullptr;
	Actor* effectActor = nullptr;
	Actor* parentActor = nullptr;

	bool isInvincible = false;
	bool isHostile = false;
	bool isDied = false;

	int team = 0; // 0 
	int actType = -1;
	int direct = 0;

	int hp = 0;
	int mp = 0;
	int sp = 0;
	int exp = 0;
	int lv = 1;

	Vector3 _attack1Range = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 _attack2Range = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 _hitRange = Vector3(0.0f, 0.0f, 0.0f);

	float _culmulatedTime_heal = 0.0f;
	float _culmutatedTIme = 0.0f;
	float _delay = -1.0f;
	bool _hitStack = false;
	float tippingPoint = 0;
	bool isStanding = false;
	bool isSuperArmor = false;
	bool isProtagonist = false;

	float _speedFactor = 0.0f;
	float _jumpFactor = 0.0f;

	int mode = 0;   // 0 = runAway 1 = attack1  2 = attack2  3 = Gaurd 
};