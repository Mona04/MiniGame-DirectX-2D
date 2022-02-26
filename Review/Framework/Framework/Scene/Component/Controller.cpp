#include "Framework.h"
#include "Controller.h"

Controller::Controller(Context* context)
	:IComponent(context)
{
	type = ComponentType::Controller;
	timer = context->GetSubsystem<Timer>();
	sceneManager = context->GetSubsystem<SceneManager>();
	monsterManager = context->GetSubsystem<MonsterManager>();
	physcisManager = context->GetSubsystem<PhysicsManager>();
	dialogManager = context->GetSubsystem<DialogManager>();
	dataManager = context->GetSubsystem<DataManager>();
	uiManager = context->GetSubsystem<UIManager>();
	resourceManager = context->GetSubsystem<ResourceManager>();
	gameManager = context->GetSubsystem<GameManager>();
}

Controller::~Controller()
{
}

void Controller::Update()
{
	if (effectActor)
	{
		if (effectActor->IsActive() == false)
		{
			effectActor = nullptr;
		}
		else
		{
			Vector3 pos = transform->GetPosition();
			pos.y -= transform->GetScale().y * 0.5f;
			pos.y += effectActor->GetComponent<Transform>()->GetScale().y * 0.5f;
			effectActor->GetComponent<Transform>()->SetPosition(pos);
		}
	}
}

void Controller::SetActor(class Actor* actor)
{
	this->actor = actor;
	renderable = actor->GetComponent<Renderable>();
	transform = actor->GetComponent<Transform>();
	rigidBody = actor->GetComponent<RigidBody>();
	animator = actor->GetComponent<Animator>();
}

void Controller::Stand()
{
	if (!Tuning()) return;

	if (actType != 0)
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//stand_info.txt");
	actType = 0;

	_culmulatedTime_heal += timer->GetDeltaTimeMs();
	if (_culmulatedTime_heal >= 500.0f)
	{
		_culmulatedTime_heal = 0.0f;
		this->Heal(this->hp / 17.0f + data_mob->_maxHp / 100.0f + 1, this->mp /17.0f + data_mob->_maxMp / 100.0f + 1, this->sp / 9.0f + data_mob->_maxSp / 100.0f + 1);
	}
}

void Controller::Walk(const int& direct)
{
	if (!Tuning()) return;

	if (actType != 1)
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//walk_info.txt");
	animator->SetReversed(direct == 1);

	Vector3 vector = direct == 0 ? Vector3(-data_mob->_speed / 2.0f, 0, 0) : Vector3(data_mob->_speed / 2.0f, 0, 0);
	actType = 1;
	this->direct = direct;
	
	_culmulatedTime_heal += timer->GetDeltaTimeMs();
	if (_culmulatedTime_heal >= 500.0f)
	{
		_culmulatedTime_heal = 0.0f;
		this->Heal(this->hp / 25.0f + data_mob->_maxHp / 200.0f + 1, this->mp / 25.0f + data_mob->_maxMp / 200.0f + 1, this->sp / 20.0f + data_mob->_maxSp / 100.0f + 1);
	}

	rigidBody->Move(vector * timer->GetDeltaTimeMs() / 34.f);
}

void Controller::Run(const int& direct)
{
	if (!Tuning()) return;
	
	if (actType != 2)
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//run_info.txt");
	animator->SetReversed(direct == 1);

	Vector3 vector = direct == 0 ? Vector3(-data_mob->_speed - _speedFactor , 0, 0) : Vector3(data_mob->_speed + _speedFactor, 0, 0);
	actType = 2;
	this->direct = direct;

	_culmulatedTime_heal += timer->GetDeltaTimeMs();
	if (_culmulatedTime_heal >= 500.0f)
	{
		_culmulatedTime_heal = 0.0f;
		this->Heal(0, this->mp / 20.0f + data_mob->_maxMp / 200.0f + 1, this->sp / 15.0f + data_mob->_maxSp / 200.0f + 1);
	}

	rigidBody->Move(vector * timer->GetDeltaTimeMs() / 34.f);
}

void Controller::Jump()
{
	if (!Tuning()) return;

	if (actType != 3)
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//jump_info.txt");
	actType = 3;

	rigidBody->Jump(Vector3(0, data_mob->_jump + _jumpFactor, 0));
}

void Controller::Gaurd()
{
	if (!CalcConsumed(data_guard)) return;
	if (!Tuning()) return;

	if (actType != 4)
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//stand_info.txt");
	actType = 4;

	monsterManager->Load_Skill_Effect(*actor, data_guard, animator->IsReversed());
	_delay = data_guard->_delay_actor;

	resourceManager->Load<AudioClip>("Effect/Attack.mp3")->Play();
}

void Controller::Attack1() // 약공
{
	if (!CalcConsumed(data_attack1)) return;
	if (!Tuning() || !data_attack1) return;

	if (actType != 5)
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//Attack1_info.txt");
	actType = 5;

	monsterManager->Load_Skill_Effect(*actor, data_attack1, animator->IsReversed());
	_delay = data_attack1->_delay_actor;

	resourceManager->Load<AudioClip>("Effect/Attack.mp3")->Play();
}

void Controller::Attack2()  // 강공
{
	if (!CalcConsumed(data_attack2)) return;
	if (!Tuning() || !data_attack2) return;

	if (actType != 6)
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//Attack2_info.txt");
	actType = 6;

	monsterManager->Load_Skill_Effect(*actor, data_attack2, animator->IsReversed());
	_delay = data_attack2->_delay_actor;

	resourceManager->Load<AudioClip>("Effect/Attack.mp3")->Play();
}

void Controller::Hit(Data_Skill* effect_data, Controller* attacker, const Vector3& knockBack, const float& damageFactor)
{
	if (!data_mob) return;
	
	if (actType != 7)
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//hit_info.txt");

	actType = 7;
	isInvincible = true;
	isHostile = true;
	_hitStack = true;

	attackActor = attacker->GetActor();
	CalcDamage(effect_data->_damage_fire * damageFactor, effect_data->_damage_water, effect_data->_damage_light, effect_data->_damage_dark, damageFactor);
	
	this->Heal(0, data_mob->_maxMp / 30.0f + 1, data_mob->_maxSp / 20.0f + 1);

	if (this->hp <= 0)
	{
		if(attacker->lv < this->lv + 5)
			attacker->ObtainExp(this->data_mob->_maxExp * 0.8f);
		else if (attacker->lv < this->lv + 10)
			attacker->ObtainExp(this->data_mob->_maxExp * 0.4f);
		else 
			attacker->ObtainExp(this->data_mob->_maxExp * 0.1f);
	}

	if (!isSuperArmor)
		rigidBody->KnockBack(knockBack);

	_delay = effect_data->_delay_hit;

	resourceManager->Load<AudioClip>("Effect/Hit.mp3")->Play();
}

void Controller::Die()
{
	if (actType != 8)
	{
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//die_info.txt");
		animator->GetAnimation()->SetRepeatType(RepeatType::Once);
	}

	actType = 8;
	isInvincible = true;

	if (animator->IsPause())
	{
		switch (Math::Random(0, 4))
		{
		case 0: monsterManager->Load_Dropped_Item(dataManager->GetItemData(data_mob->_dropItemCode1), transform->GetPosition()); break;
		case 1: monsterManager->Load_Dropped_Item(dataManager->GetItemData(data_mob->_dropItemCode2), transform->GetPosition()); break;
		case 2:	monsterManager->Load_Dropped_Item(dataManager->GetItemData(data_mob->_dropItemCode3), transform->GetPosition()); break;
		case 3:	monsterManager->Load_Dropped_Item(dataManager->GetItemData(data_mob->_dropItemCode4), transform->GetPosition()); break;
		}
		this->actor->SetActive(false);
		isDied = true;
		resourceManager->Load<AudioClip>("Effect/Die.mp3")->Play();
		resourceManager->Load<AudioClip>("Effect/ItemDrop.mp3")->Play();
	}
}

void Controller::SuperJump(const int& factor)
{
	if (!Tuning()) return;
	if (!rigidBody->IsOnGroundFlag(GroundFlag::GroundFlag_Bottom))
		return;

	if (context->GetSubsystem<InventoryManager>()->DeleteItem_Auto("Powder_Magic", 1) == true)
	{
		if (actType != 3)
			animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//jump_info.txt");
	
		actType = 3;

		rigidBody->Jump(Vector3(0, data_mob->_jump * 3.0f, 0));
	}
}

void Controller::Heal(const int& hp_var, const int& mp_var, const int& sp_var)
{
	if (this->hp <= 0)
		return;

	this->hp += hp_var;
	if (hp > GetMaxHP())
		hp = GetMaxHP();

	this->mp += mp_var;
	if (mp > GetMaxMP())
		mp = GetMaxMP();

	this->sp += sp_var;
	if (sp > GetMaxSP())
		sp = GetMaxSP();
}

void Controller::Resurrection()
{
	tippingPoint += timer->GetDeltaTimeMs();
	if (tippingPoint > 100000.f)
	{
		this->hp = data_mob->_maxHp;
		this->mp = data_mob->_maxMp;
		this->sp = data_mob->_maxSp;
		isDied = false;
		isInvincible = false;
		if (IsSuperArmor() == false)
		{
			attackActor = nullptr;
			isHostile = false;
		}
		this->actor->SetActive(true);
	}
}

void Controller::Portal()
{
	if (targetActor == nullptr || !Tuning())
		return;

	if (targetActor->HasComponent<Controller>())
	{
		Data_Portal* portalData = targetActor->GetComponent<Controller>()->GetPortalData();
		if (portalData)
			monsterManager->Teleport(portalData->_destSceneName, actor->GetName(), portalData->_destPos);	
	}
}

void Controller::Teleport(const Vector3& pos)
{
	transform->SetPosition(pos);
	rigidBody->GetBoundBox().Init(transform);
}

void Controller::Dialog()
{
	if (targetActor == nullptr || !Tuning())
		return;

	if (targetActor->HasComponent<Controller>())
	{
		Data_Dialog* dialogData = targetActor->GetComponent<Controller>()->GetDialogData();
		if (dialogData)
		{
			uiManager->SetCurrentUI("Dialogs");
			dialogManager->DialogSetScript(dialogData->GetDialogScriptPath(), dialogData);  // you don't insert data_dialog as it is mine not others
		}
	}
}

void Controller::Evolution(const std::string& name)
{
	Actor* tmp_actor = new Actor(context);
	{
		tmp_actor->LoadFromFile("../../_Assets/Scene/Mobs/" + name + ".actor");
		auto tmpController = tmp_actor->GetComponent<Controller>();
		this->data_mob = tmpController->GetMobData();
		this->data_attack1 = tmpController->GetAttack1Data();
		this->data_attack2 = tmpController->GetAttack2Data();
		this->data_guard = tmpController->GetGuardData();
		this->data_dialog = tmpController->GetDialogData();
		this->data_portal = tmpController->GetPortalData();
		SetMobData(data_mob);
		this->lv = data_mob->_defaultLv - 3 > 1 ? data_mob->_defaultLv - 3 : 1 ;
		this->_jumpFactor = 0;
		this->_speedFactor = 0;
	}
	SAFE_DELETE(tmp_actor);

	context->GetSubsystem<MonsterManager>()->Load_LevelUp_Effect(this);

	rigidBody->GetBoundBox().Translate(Vector3(0, 120, 0));
	rigidBody->Translate_Tmp();
	rigidBody->Translate();
}

void Controller::LevelUp()
{
	if (isDied == true) return;

	this->lv += 1;
	this->exp = 0;
	this->hp = GetMaxHP();
	this->mp = GetMaxMP();
	this->sp = GetMaxSP();

	context->GetSubsystem<MonsterManager>()->Load_LevelUp_Effect(this);
}

void Controller::ObtainExp(const int& exp)
{
	this->exp += exp;
	if (GetMaxExp() <= this->exp)
		LevelUp();
}

void Controller::RandomSkillChange()
{
	int skillLv = data_mob->_defaultLv / 10 + 1;
	std::vector<std::string> cores = { "water" , "dark", "fire", "light" };
	
	auto tmpAttack1 = dataManager->GetData<Data_Skill>("attack1_" + cores[Math::Random(0, 4)] + "_lv" + std::to_string(skillLv));
	if (tmpAttack1)
		this->data_attack1 = tmpAttack1;

	auto tmpAttack2 = dataManager->GetData<Data_Skill>("attack2_" + cores[Math::Random(0, 4)] + "_lv" + std::to_string(skillLv));
	if (tmpAttack2)
		this->data_attack2 = tmpAttack2;
}

void Controller::RandomRGBChange()
{
	if (actor && actor->HasComponent<Renderable>())
	{
		actor->GetComponent<Renderable>()->GetMaterial()->SetAlbedoColor(
			Color4((float)Math::Random(0, 120) / 100.0f, (float)Math::Random(0, 120) / 100.0f, (float)Math::Random(0, 120) / 100.0f, 1));
	}
}

void Controller::ChangeMobData(const std::string& name)
{
	auto data = dataManager->GetData<Data_Mob>(name);
	SetMobData(data);
	this->Stand();
}

void Controller::ChangeScale(const Vector3& scale)
{
	this->transform->SetScale(scale);
	this->rigidBody->GetBoundBox().SetSize(scale);
}

void Controller::RandomAttack(float time, float percent1, float percent2, float percent3)
{
	if (!attackActor) return;

	tippingPoint += timer->GetDeltaTimeMs();

	if (_hitStack == true)  // if attacked, automatically attack 
	{
		_hitStack = false;
		mode = Math::Random(1, 4);
	}
	else if (tippingPoint >= time)
	{
		tippingPoint = 0;
		mode = Math::Random(0, 100);
		mode = mode < percent1 * 100.0f ? 1 : mode < (percent1 + percent2) * 100.0f ? 2 : mode < (percent1 + percent2 + percent3) * 100.0f ? 3 : 0;
	}

	Transform* _trans_prot = attackActor->GetComponent<Transform>();
	Vector3 _move_distance = _trans_prot->GetPosition() - this->transform->GetPosition();

	if (mode != 3)
	{
		if (Math::Random(0, 1) == 0)
			AttackAuto(0);
		else
			AttackAuto(1);
	}

	switch (mode)
	{
	case 0:  // keep protagonist in check
	{		
		if (_move_distance.x > 0)
		{
			_move_distance -= this->transform->GetScale() * 0.5f;  // differ by cases

			if (_move_distance.x > this->_hitRange.x + 50.0f)  // far enough
				direct = 1;
			else if (_move_distance.x < this->_hitRange.x + 5.0f)   // too close 
				direct = 0;
		}
		else
		{
			_move_distance += this->transform->GetScale() * 0.5f;  // differ by cases

			if (- _move_distance.x > this->_hitRange.x + 50.0f)  // far enough
				direct = 0;
			else if (- _move_distance.x < this->_hitRange.x + 5.0f)   // too close 
				direct = 1;
		}

		MoveAuto();
		break;
	}
	case 1:  // attack1
	{
		if (_move_distance.x > 0)
		{
			_move_distance = _move_distance - _trans_prot->GetScale() * 0.5f;
			direct = 1;
			MoveAuto();
			if (_move_distance.x < this->_attack1Range.x)  // is enemy on the attack1 range?
			{
				Attack1();
				mode = 0;
			}
		}
		else
		{
			_move_distance = _move_distance + _trans_prot->GetScale() * 0.5f;  // differ by cases
			direct = 0;
			MoveAuto();
			if (_move_distance.x > this->_attack1Range.x)  // is enemy on the attack1 range?
			{
				Attack1();
				mode = 0;
			}
		}
		break;
	}
	case 2:  // attack2
	{
		if (_move_distance.x > 0)
		{
			_move_distance = _move_distance - _trans_prot->GetScale() * 0.5f;
			direct = 1;
			MoveAuto();
			if (_move_distance.x < this->_attack2Range.x)  // is enemy on the attack1 range?
			{
				Attack2();
				mode = 0;
			}
		}
		else
		{
			_move_distance = _move_distance + _trans_prot->GetScale() * 0.5f;  // differ by cases
			direct = 0;
			MoveAuto();
			if (_move_distance.x > this->_attack2Range.x)  // is enemy on the attack1 range?
			{
				Attack2();
				mode = 0;
			}
		}
		break;
	}
	case 3:  // gaurd
	{
		Gaurd(); 
		mode = 0;
		break;
	}
	}
}

void Controller::RandomWalk(float time)
{
	tippingPoint += timer->GetDeltaTimeMs();
	if (tippingPoint >= time)
	{
		tippingPoint = 0;
		switch (Math::Random(0, 3))
		{
		case 0:  // left
			direct = 0; isStanding = false;
			break;
		case 1: // right
			direct = 1; isStanding = false;
			break;
		case 2:
			isStanding = true;
			break;
		}
	}
	if (isStanding)
		Stand();
	else
		MoveAuto(1);
}

void Controller::RandomRun(float time)
{
	tippingPoint += timer->GetDeltaTimeMs();
	if (tippingPoint >= time)
	{
		tippingPoint = 0;
		switch (Math::Random(0, 2))
		{
		case 0:
			direct = 0;
			isStanding = true;
			break;
		case 1:
			direct = 1;
			isStanding = true;
			break;
		case 2:
			isStanding = false;
			break;
		}
	}
	if (!isStanding)
	{
		Stand();
		return;
	}

	MoveAuto(0);
}

bool Controller::Tuning()
{
	if (!this->data_mob)
		return false;

	if (hp <= 0)
	{
		if (!isDied)
		{
			Die();
			tippingPoint = 0;
		}
		return false;
	}
	if (_delay > 0)
	{
		_culmutatedTIme += timer->GetDeltaTimeMs();
		if (_culmutatedTIme > _delay)
		{
			_delay = -1.0f;
			_culmutatedTIme = 0.0f;
			isInvincible = false;
			return true;
		}
		else
			return false;
	}
	if (isInvincible)
		isInvincible = false;
	if (isDied)
		isDied = false;

	return true;
}

bool Controller::CalcConsumed(Data_Skill* skill)
{
	if (hp > skill->_hp_consumed && mp > skill->_mp_consumed && sp > skill->_sp_consumed)
	{
		hp -= skill->_hp_consumed;
		mp -= skill->_mp_consumed;
		sp -= skill->_sp_consumed;
		return true;
	}
	else
		return false;
}

int Controller::CalcDamage(const float& damage_fire, const float& damage_water, const float& damage_light, const float& damage_dark, const float& damageFactor)
{
	int damage = Math::Clamp<float>(damage_fire - data_mob->_def_fire, 0, 99999) + damage_fire * 0.5f
		+ Math::Clamp<float>(damage_water - data_mob->_def_water, 0, 99999) + damage_water * 0.5f
		+ Math::Clamp<float>(damage_light - data_mob->_def_light, 0, 99999) + damage_light * 0.5f
		+ Math::Clamp<float>(damage_dark - data_mob->_def_dark , 0, 99999) + damage_dark * 0.5f * damageFactor;
	this->hp -= damage;
	return 1;
}

void Controller::MoveAuto(const int& isWalk)
{
	auto scanned_result = physcisManager->ScanField(transform->GetPosition(), transform->GetScale(), direct);
	switch (scanned_result)
	{
	case ScannedResult::Cliff:
	case ScannedResult::Wall:
		direct = direct == 1 ? 0 : 1;
		break;
	case ScannedResult::Stair_Lower:
	case ScannedResult::Flat:
		isWalk ? Walk(direct) : Run(direct);
		break;
	case ScannedResult::Stair_Upper:
		Jump();
	}
}

bool Controller::AttackAuto(const int& type)
{
	Transform* _trans_prot = gameManager->GetProtagonist()->GetComponent<Transform>();
	Vector3 _move_distance = _trans_prot->GetPosition() - this->transform->GetPosition();

	if (_move_distance.x > 0)
	{
		_move_distance = _move_distance - _trans_prot->GetScale() * 0.5f;;
		if (type == 1)
		{
			if (_move_distance.x < this->_attack1Range.x)  // is enemy on the attack1 range?
			{
				direct = 1;
				MoveAuto();
				Attack1();
				return true;
			}
		}
		else if (type == 2)
		{
			if (_move_distance.x < this->_attack2Range.x)  // is enemy on the attack1 range?
			{
				direct = 1;
				MoveAuto();
				Attack2();
				return true;
			}
		}

	}
	else
	{
		_move_distance = _move_distance + _trans_prot->GetScale() * 0.5f;  // differ by cases
		if(type == 1)
		{
			if (_move_distance.x > -this->_attack1Range.x)  // is enemy on the attack1 range?
			{
				direct = 0;
				MoveAuto();
				Attack1();
				return true;
			}
		}
		else if (type == 2)
		{
			if (_move_distance.x > -this->_attack2Range.x)  // is enemy on the attack1 range?
			{
				direct = 0;
				MoveAuto();
				Attack2();
				return true;
			}
		}
	}
	return false;
}

const float Controller::GetLVFactor()
{
	if (!data_mob) 
		return 0; 

	return (this->lv > data_mob->_defaultLv ? (1 + 0.05f * (this->lv - this->data_mob->_defaultLv)) : 1.0f) + (isProtagonist ? 1.0f : 0);
}

void Controller::SetJumpFactor(const float& var)
{
	_jumpFactor = var; 
	auto result = Vector3(rigidBody->GetMaxLimit().x, 10.0f, 0) + Vector3(0, var, 0);
	if(result.x < 20 && result.y < 18)
		rigidBody->SetMaxLimit(Vector3(rigidBody->GetMaxLimit().x, 10.0f, 0) + Vector3(0, var, 0));
}

void Controller::SetSpeedFactor(const float& var)
{
	_speedFactor = var; 
	auto result = Vector3(+data_mob->_speed * 2.0f, rigidBody->GetMaxLimit().y, 0) + Vector3(var, 0, 0);
	if(result.x < 20 && result.y < 18)
		rigidBody->SetMaxLimit(Vector3(+data_mob->_speed * 2.0f, rigidBody->GetMaxLimit().y, 0) + Vector3(var, 0, 0));
	
	result = Vector3(-data_mob->_speed * 2.0f, rigidBody->GetMinLimit().y, 0) - Vector3(var, 0, 0);
	if(result.x > -20 && result.y > -18)
		rigidBody->SetMinLimit(Vector3(-data_mob->_speed * 2.0f, rigidBody->GetMinLimit().y, 0) - Vector3(var, 0, 0));
}

void Controller::SetMobData(Data_Mob* data)
{
	if (!data || data->GetName() == "") return;

	this->data_mob = data;
	this->hp = data->_maxHp;
	this->mp = data->_maxMp;
	this->sp = data->_maxSp;
	this->exp = 0;
	this->lv = data->_defaultLv;

	auto filepathsTexture = FileSystem::GetFilesInDirectory("../../_Assets/Texture/Characters/" + data_mob->_mobName);
	for (auto filepath : filepathsTexture)
	{
		resourceManager->Load<Texture>(filepath, filepath);
	}

	auto filepathsAnimation = FileSystem::GetFilesInDirectory("../../_Assets/Animation/characters/" + data_mob->_mobName);
	for (auto filepath : filepathsAnimation)
	{
		resourceManager->Load<Animation>(filepath, filepath);
	}

	if (animator)
	{
		animator->ResetWeight();
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//walk_info.txt");
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//run_info.txt");
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//jump_info.txt");
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//attack1_info.txt");
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//attack2_info.txt");
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//hit_info.txt");
		animator->SetAnimation_Script("//characters//" + data_mob->_mobName + "//die_info.txt");
		animator->SetAnimation("//characters//" + data_mob->_mobName + "//stand_info.txt",
			"//characters//" + data_mob->_mobName + "//stand_info.txt",  renderable);
	}
	if (rigidBody)
	{
		rigidBody->GetBoundBox().SetSize(Vector3(data->_sizeX, data->_sizeY, 0));
		rigidBody->SetMaxLimit(Vector3(+data_mob->_speed * 2.0f, +10.0f, 0));
		rigidBody->SetMinLimit(Vector3(-data_mob->_speed * 2.0f, -10.0f, 0));
	}	
	if (transform)
	{
		transform->SetScale(Vector3(data->_sizeX, data->_sizeY, 0));
	}
}

void Controller::SetAttack1Data(Data_Skill* data)
{
	this->data_attack1 = data;
	this->_attack1Range = data_attack1->_distance + data_attack1->_size_stand * 0.5f;
}

void Controller::SetAttack2Data(Data_Skill* data)
{
	this->data_attack2 = data;
	this->_attack2Range = data_attack2->_distance + data_attack2->_size_stand * 0.5f;
}
