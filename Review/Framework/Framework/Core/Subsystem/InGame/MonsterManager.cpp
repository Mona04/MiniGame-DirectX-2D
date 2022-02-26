#include "Framework.h"
#include "MonsterManager.h"
#include "Framework/Core/Engine.h"

MonsterManager::MonsterManager(Context* context)
	: ISubsystem(context)
{
	EventSystem::Get()->Subscribe(EventType::Update, EVENT_HANDLER(Update));

	sceneManager = context->GetSubsystem<SceneManager>();
	uiManager = context->GetSubsystem<UIManager>();
	dataManager = context->GetSubsystem<DataManager>();
	thread = context->GetSubsystem<Thread>();
}

MonsterManager::~MonsterManager()
{
	Clear();

	for (auto& pair : effects_map)
	{
		for (auto& effect : pair.second)
			SAFE_DELETE(effect);
	}
	effects_map.clear();

	SAFE_DELETE(hp_Bar);
	SAFE_DELETE(hp_Bar_Geometry_Frame);
	SAFE_DELETE(hp_Bar_Geometry_Gauge);
	SAFE_DELETE(hp_Bar_InstanceBuffer_Frame);
	SAFE_DELETE(hp_Bar_InstanceBuffer_Gauge);
}

const bool MonsterManager::Initialize()
{
	Clear();
	Init_Common_Actors();
	Init_HP_Gauges();

	return true;
}

void MonsterManager::Update()
{
	if (ProgressReport::Get()->GetIsLoadingOfReport(ProgressReport::Scene))
		return;

	Update_Monsters();
	Update_MonsterHP();
	Update_LevelUpEffect();
	Update_Dropped_Item();
	Update_SkillEffect();
}

void MonsterManager::Clear()
{
	if(hp_Bar_InstanceBuffer_Frame)
		hp_Bar_InstanceBuffer_Frame->Clear();
	
	if (hp_Bar_InstanceBuffer_Gauge)
		hp_Bar_InstanceBuffer_Gauge->Clear();

	if(hp_Bar_Geometry_Frame)
		hp_Bar_Geometry_Frame->Clear();

	if (hp_Bar_Geometry_Gauge)
		hp_Bar_Geometry_Gauge->Clear();

	monsters.clear();
	monsters.shrink_to_fit();
}

void MonsterManager::Clear_()
{
	monsters.clear();
	monsters.shrink_to_fit();

	for (auto& map : effects_map)
	{
		for (auto& effect : map.second)
			effect->SetActive(false);
	}
	evolution = nullptr; 
}

void MonsterManager::Clear_Monsters()
{
	for (auto& monster : monsters)
		SAFE_DELETE(monster);
}

void MonsterManager::ToggleEvolution()
{
	if (!evolution)
		evolution = context->GetSubsystem<UIManager>()->GetCurrentUI()->GetComponent<Evolution>();
	
	if (!evolution) return;

	if (evolution->GetIsVisible())
		evolution->SetIsVisible(false);
	else
	{
		evolution->SetIsVisible(true);
		UpdateEvolutionData();
	}
	
}

void MonsterManager::UpdateEvolutionData()
{
	if (!evolution)
		evolution = context->GetSubsystem<UIManager>()->GetCurrentUI()->GetComponent<Evolution>();

	if(evolution) evolution->UpdateSlots();
}

void MonsterManager::Spawn(const std::string& path, const SpawnInfo& info, const int& team)
{
	static uint mob_num = 0;
	mob_num += 1;
	if (mob_num >= 100000)
		mob_num = 0;

	Actor* actor = new Actor(context);
	
	if (path != NULL_STRING)
		actor->LoadFromFile(path);

	if (actor->HasComponent<Transform>()) actor->GetComponent<Transform>()->SetPosition(info.pos);
	if (actor->HasComponent<RigidBody>()) actor->GetComponent<RigidBody>()->GetBoundBox().Init(actor->GetComponent<Transform>());
	if (actor->HasComponent<Controller>()) actor->GetComponent<Controller>()->SetTeam(team);
	if (actor->HasComponent<Controller>() && info.isAgressive)
	{
		Controller* controller = actor->GetComponent<Controller>();
		controller->SetAttackActor(context->GetSubsystem<GameManager>()->GetProtagonist());
		controller->SetSuperArmor(true);
	}
	
	actor->SetName(FileSystem::GetIntactFileNameFromPath(path) + std::to_string(mob_num));
	actor->SetActive(false);

	monsters.emplace_back(actor);

	context->GetSubsystem<Renderer>()->UpdateActorList(actor);
	context->GetSubsystem<PhysicsManager>()->AddActor(actor);
}

void MonsterManager::SpawnAuto(const std::string& name, int team, bool isAgressive)
{
	std::string path = "../../_Assets/Scene/Mobs/" + name + ".actor";
	Vector3 pos = context->GetSubsystem<GameManager>()->GetProtagonist()->GetComponent<Transform>()->GetPosition();
	Spawn(path, SpawnInfo(pos + Vector3(0, 200.0f, 0), isAgressive), team);
}

void MonsterManager::SetSpawnList(Data_Spawn* data, int team)
{
	if (!data) return;

	Clear_Monsters();

	std::string path, name;
	for (const auto& _info : data->_spawnInfoList)
	{
		name = data->_mobList[Math::Random(0, data->_mobList.size())];
		path = "../../_Assets/Scene/Mobs/" + name + ".actor";
		Spawn(path, _info, team);
	}
}

void MonsterManager::Load_LevelUp_Effect(Controller* controller)
{
	for (auto& effect : effects_map[MonsterEffectType::LevelUp])
	{
		if (effect->IsActive() == false)
		{
			effect->SetTimeLimit(2100);
			effect->SetActive(true);
			effect->GetComponent<Animator>()->Play_Start();
			effect->GetComponent<Transform>()->SetScale(controller->GetScale() * 3.0f);
			controller->SetEffectActor(effect);
			break;
		}
	}
}

void MonsterManager::Load_Dropped_Item(Data_Item* data, const Vector3& pos)
{
	if (!data) return;

	for (auto& effect : effects_map[MonsterEffectType::Dropped_Item])
	{
		if (effect->IsActive() == false)
		{
			effect->SetTimeLimit(60000);
			effect->SetActive(true);
			effect->GetComponent<Controller>()->SetItemData(data);
			effect->GetComponent<Renderable>()->SetTexture(TextureType::Albedo, data->_imagePath, data->_imagePath);

			if(data->_sizeX == 1 && data->_sizeY == 1)
				effect->GetComponent<Transform>()->SetScale(Vector3(data->_sizeX * BLOCK_SIZE, data->_sizeY * BLOCK_SIZE, 0));
			else
				effect->GetComponent<Transform>()->SetScale(Vector3(data->_sizeX * BLOCK_SIZE * 0.5f, data->_sizeY * BLOCK_SIZE * 0.5f, 0));
			effect->GetComponent<Transform>()->SetPosition(Vector3(((int)pos.x / 30) * 30 + 5.0f, (int)pos.y, (int)pos.z));
			effect->GetComponent<RigidBody>()->GetBoundBox().Init(effect->GetComponent<Transform>());
			effect->GetComponent<RigidBody>()->GetBoundBox().SetSize(Vector3(BLOCK_SIZE, BLOCK_SIZE, 0));
			break;
		}
	}
}

// Pool 에 저장된거 하나 꺼내오기
void MonsterManager::Load_Skill_Effect(Actor& ownerActor, Data_Skill* data, bool direct, const AnimationMotionType& type)
{
	if (!data) return;

	std::string path;
	Vector3 pos;
	Vector3 size_rigid = Vector3(0, 0, 0);
	Vector3 size_effect = Vector3(0, 0, 0);
	float delay;
	switch (type)
	{
	case AnimationMotionType::Stand:
		path = "//skills//" + data->_skillName + "//stand_info.txt";
		if (data->_skillName == "")
			int a = 0;
		pos = (direct ? Vector3(data->_distance.x, data->_distance.y, 0) : Vector3(-data->_distance.x, data->_distance.y, 0))
			+ ownerActor.GetComponent<Transform>()->GetPosition();
		size_effect = data->_size_stand;
		size_rigid = data->_size_stand;
		delay = data->_delay_stand;
		break;
	case AnimationMotionType::Walk: path = "//skills//" + data->_skillName + "//walk_info.txt"; break;
	case AnimationMotionType::Run: path = "//skills//" + data->_skillName + "//run_info.txt"; break;
	case AnimationMotionType::Jump: path = "//skills//" + data->_skillName + "//jump_info.txt"; break;
	case AnimationMotionType::Attack1: path = "//skills//" + data->_skillName + "//attack1_info.txt"; break;
	case AnimationMotionType::Attack2: path = "//skills//" + data->_skillName + "//attack2_info.txt"; break;
	case AnimationMotionType::Hit:
		path = "//skills//" + data->_skillName + "//hit_info.txt";
		pos = ownerActor.GetComponent<Transform>()->GetPosition();
		size_effect = data->_size_hit;
		size_rigid = Vector3(-1, -1, -1);
		delay = data->_delay_hit > 0 ? data->_delay_hit : 1;
		break;
	case AnimationMotionType::Die: path = "//skills//" + data->_skillName + "//die_info.txt"; break;
	}

	for (auto& actor : effects_map[MonsterEffectType::Skill_Effect])
	{
		if (!actor->IsActive())
		{
			actor->SetActive(true);
			actor->GetComponent<Animator>()->SetAnimation(path, path, nullptr);
			actor->GetComponent<Animator>()->Play(1.5);
			actor->GetComponent<Controller>()->SetAttack1Data(data);
			actor->GetComponent<Controller>()->SetTeam(ownerActor.GetComponent<Controller>()->GetTeam());
			actor->GetComponent<Controller>()->SetActType(ownerActor.GetComponent<Controller>()->GetActType());
			actor->GetComponent<Controller>()->SetDirect(direct ? 1 : 0);
			actor->GetComponent<Controller>()->SetParentActor(&ownerActor);
			actor->SetTimeLimit(delay);

			Transform* transform = actor->GetComponent<Transform>();
			RigidBody* rigidBody = actor->GetComponent<RigidBody>();
			Animator* animator = actor->GetComponent<Animator>();

			transform->SetPosition(pos);
			transform->SetScale(size_effect);
			rigidBody->SetRigidBodyType(RigidBodyType::Effect);
			rigidBody->SetBoundBoxAndTransform(transform);
			rigidBody->GetBoundBox().SetSize(size_rigid);
			rigidBody->GetBoundBox().SetCenter(type == AnimationMotionType::Hit ? Vector3(-9999999.0f, 0, 0) : pos);
			animator->SetReversed(direct);
			
			return;
		}
	}

	//Resize_Skill_Effect();
	//Load_Skill_Effect(ownerActor, data, direct, type);
}

// 이 왜 여기잇지 ㅋㅋㅋㅋㅋㅋㅋㅋ
void MonsterManager::Teleport(const std::string& sceneName, const std::string& actorName, const Vector3& pos)
{
	Thread* thread = context->GetSubsystem<Thread>();
	ProgressBar* bar = context->GetSubsystem<UIManager>()->GetCurrentPreUI()->GetComponent<ProgressBar>();
	thread->AddTask([this, bar, sceneName, actorName, pos]()
		{
			auto k = context->GetSubsystem<GameManager>()->GetProtagonist();
			context->GetSubsystem<ResourceManager>()->Set_TemperateMode(true);
			ProgressReport* reporter = ProgressReport::Get();
			reporter->SetDefault(ProgressReport::Scene, 4, context->GetSubsystem<UIManager>()->GetCurrentPreUI()->GetComponent<ProgressBar>());
			{
				while (!context->GetEngine()->DoesUpdateEnd());

				Clear_();
				context->GetSubsystem<ResourceManager>()->Clear_Temperate();
				reporter->OneStepForward(ProgressReport::Scene);

				sceneManager->MoveActorOtherScene(sceneName, actorName, pos);
				reporter->OneStepForward(ProgressReport::Scene);

				SetSpawnList(dataManager->GetData<Data_Spawn>(sceneName));
				reporter->OneStepForward(ProgressReport::Scene);

				context->GetSubsystem<GameManager>()->SetBgm(sceneManager->GetScenes()[sceneName]->GetDataField()->_bgmPath);
				while (context->GetSubsystem<Thread>()->LeftJobs() > 1)
					Sleep(500.0f);
				reporter->OneStepForward(ProgressReport::Scene);
			}
			context->GetSubsystem<ResourceManager>()->Set_TemperateMode(false);

			// 이동후 대화로 자동으로 넘어가게 함. (사실 스크립트로 넘어가야하긴 하는데)
			for (int i = 1; i < 17; i++)
			{
				if (sceneName.find("Floor"+std::to_string(i)) != std::string::npos)
				{
					uiManager->SetCurrentUI("Dialogs");
					context->GetSubsystem<DialogManager>()->DialogSetScript("Dialog/Floor" + std::to_string(i) + "Morian_Frame.as", 
						dataManager->GetData<Data_Dialog>("Floor" + std::to_string(i) + "Morian_Frame"));
				}
			}
		});

}

void MonsterManager::Init_Common_Actors()
{
	effects_map.emplace(std::make_pair(MonsterEffectType::LevelUp, std::vector<Actor*>()));
	effects_map.emplace(std::make_pair(MonsterEffectType::Skill_Effect, std::vector<Actor*>()));
	effects_map.emplace(std::make_pair(MonsterEffectType::Dropped_Item, std::vector<Actor*>()));

	auto& levelUp_effects = effects_map[MonsterEffectType::LevelUp];
	levelUp_effects.reserve(7);
	for (int i = 0; i < 7; i++)
	{
		Actor* levelUp_effect = levelUp_effects.emplace_back(new Actor(context));
		if (!levelUp_effect) continue;

		levelUp_effect->LoadFromFile("../../_Assets/Scene/Effect/levelUp_Effect.actor");
		levelUp_effect->SetName("LevelUp_Effect" + std::to_string(i));
		levelUp_effect->SetActive(false);
	}

	auto& dropped_items = effects_map[MonsterEffectType::Dropped_Item];
	dropped_items.reserve(100);
	for (int i = 0; i < 100; i++)
	{
		Actor* dropped_item = dropped_items.emplace_back(new Actor(context));
		if (!dropped_item) continue;

		dropped_item->LoadFromFile("../../_Assets/Scene/Effect/dropped_Item.actor");
		dropped_item->SetName("Dropped_Item" + std::to_string(i));
		dropped_item->GetComponent<RigidBody>()->SetMinLimit(Vector3(0, -7.0f, 0));
		dropped_item->SetActive(false);
	}

	auto& actorsForSkill = effects_map[MonsterEffectType::Skill_Effect];
	actorsForSkill.reserve(20);
	for (int i = 0; i < 20; i++)
	{
		Actor* actor = new Actor(context);
		if (!actor) continue;

		Renderable* renderable = actor->AddComponent<Renderable>();
		actor->AddComponent<RigidBody>();
		actor->AddComponent<Transform>();
		actor->AddComponent<Controller>();
		renderable->SetMaterial("Ex.material");
		renderable->SetMesh("QUAD.mesh");
		Animator* animator = actor->AddComponent<Animator>();
		animator->SetAnimation("//characters//slime//stand_info.txt", "slime stand", renderable);
		actor->SetName("Skill " + std::to_string(i));
		actor->SetActive(false);
		actor->Update();
		actorsForSkill.emplace_back(actor);
	}
}

void MonsterManager::Init_HP_Gauges()
{
	hp_Bar = new ProgressBar(context);
	hp_Bar->SetIsVisible(false);
	hp_Bar->SetName("Monster_HP_Bar");
	hp_Bar->LoadFromFile("../../_Assets/UI/UI component/Monster_HP_Bar.uicom");
	hp_Bar->SetPosition(Vector3(0.0f, 0.05f, 0.0f));
	//Vector3 scl = hp_Bar->GetScale();
	//scl.y *= 0.5f;
	//hp_Bar->SetScale(scl);

	auto frames = hp_Bar->GetFrames();
	for (auto& frame : frames)
		frame->SetIsInstanced(true);

	hp_Bar_InstanceBuffer_Frame = new VertexBuffer(context);
	hp_Bar_InstanceBuffer_Gauge = new VertexBuffer(context);
	hp_Bar_Geometry_Frame = new Geometry<VertexPositionScaleSprite>();
	hp_Bar_Geometry_Gauge = new Geometry<VertexPositionScaleSprite>();

	hp_Bar_Geometry_Frame->AddVertex(VertexPositionScaleSprite(Vector3(-0.0f, 3.2f, 0), hp_Bar->GetScale(), Vector2(0, 0)));
	hp_Bar_Geometry_Gauge->AddVertex(VertexPositionScaleSprite(Vector3(-0.0f, 3.2f, 0), hp_Bar->GetScale(), Vector2(0, 0)));
	hp_Bar_InstanceBuffer_Frame->Create<VertexPositionScaleSprite>(hp_Bar_Geometry_Frame->GetVertices(), D3D11_USAGE_DYNAMIC);
	hp_Bar_InstanceBuffer_Gauge->Create<VertexPositionScaleSprite>(hp_Bar_Geometry_Gauge->GetVertices(), D3D11_USAGE_DYNAMIC);
}

void MonsterManager::Update_Monsters()
{
	auto protagonist = context->GetSubsystem<GameManager>()->GetProtagonist();
	if (!protagonist)
		return;

	Vector2 resolution = context->GetSubsystem<Renderer>()->GetResolution();
	Vector3 _pos_protagonist = protagonist->GetComponent<Transform>()->GetPosition();
	Vector3 _distance;
	Transform* transform;
	for (auto& monster : monsters)
	{
		if (!monster) continue;
		if (transform = monster->GetComponent<Transform>())
		{
			_distance = Math::Distance(transform->GetPosition(), _pos_protagonist);

			if (_distance.x > resolution.x || _distance.y > resolution.y)
				monster->SetActive(false);
			else if (monster->GetComponent<Controller>()->IsDied())
				monster->GetComponent<Controller>()->Resurrection();
			else
			{
				monster->Update();
				monster->SetActive(true);
			}
		}
	}
}

void MonsterManager::Update_MonsterHP()
{
	hp_Bar->Update();

	if (monsters.size() < 1 || hp_Bar == nullptr)
	{
		hp_Bar_InstanceBuffer_Frame->Clear();
		hp_Bar_InstanceBuffer_Gauge->Clear();
		return;
	}

	hp_Bar_Geometry_Frame->Clear();
	hp_Bar_Geometry_Gauge->Clear();

	Camera* camera = context->GetSubsystem<Renderer>()->GetCamera(); 
	const Vector2 resolution = camera->GetResolution() / camera->GetMagFactor();
	const Vector3 origin = camera->GetPosition();
	Vector3 pos, bar_scl, gauge_scl;

	for (auto monster : monsters)
	{
		if (!monster || !monster->IsActive()) 
			continue;
		
		Controller* controller = monster->GetComponent<Controller>();
		Transform* trans = monster->GetComponent<Transform>();

		if (!controller || !trans)
			return;

		if (controller->GetActType() == 8) // die
		{
			pos = Vector3(-10, -10, 0);
		}
		else
		{
			hp_Bar->SetProgress(controller->GetHP(), controller->GetMaxHP());
			pos = trans->GetPosition(); 
			pos -= origin;
			pos.x -= trans->GetScale().x * 0.5f;
			pos.y += trans->GetScale().y * 0.5f;
			pos = 2.0f * pos / resolution;

			bar_scl = hp_Bar->GetFrame("Frame")->GetScale(); bar_scl.x *= trans->GetScale().x / 70.f;
			gauge_scl = hp_Bar->GetFrame("Gauge")->GetScale(); gauge_scl.x *= trans->GetScale().x / 70.f;
		}

		hp_Bar_Geometry_Frame->AddVertex(VertexPositionScaleSprite(pos, bar_scl, Vector2(0, 0)));
		hp_Bar_Geometry_Gauge->AddVertex(VertexPositionScaleSprite(pos, gauge_scl, Vector2(0, 0)));
	}

	if (hp_Bar_Geometry_Frame->GetVertexCount() < 1)  // if there is no item, we cannot map buffer;
	{
		hp_Bar_Geometry_Frame->Clear();
		hp_Bar_Geometry_Gauge->Clear();
		hp_Bar_Geometry_Frame->AddVertex(VertexPositionScaleSprite(Vector3(-0.0f, 2.0f, 0), hp_Bar->GetScale(), Vector2(0, 0)));
		hp_Bar_Geometry_Gauge->AddVertex(VertexPositionScaleSprite(Vector3(-0.0f, 2.0f, 0), hp_Bar->GetScale(), Vector2(0, 0)));
	}

	if (hp_Bar_Geometry_Frame->GetVertexCount() > hp_Bar_InstanceBuffer_Frame->GetVertexCount())
	{
		hp_Bar_InstanceBuffer_Frame->Clear();
		hp_Bar_InstanceBuffer_Frame->Create(hp_Bar_Geometry_Frame->GetVertices(), D3D11_USAGE_DYNAMIC);
		hp_Bar_InstanceBuffer_Gauge->Clear();
		hp_Bar_InstanceBuffer_Gauge->Create(hp_Bar_Geometry_Gauge->GetVertices(), D3D11_USAGE_DYNAMIC);
	}
	else
	{
		auto vdata = hp_Bar_InstanceBuffer_Frame->Map<VertexPositionScaleSprite>();
		{
			memcpy(vdata, hp_Bar_Geometry_Frame->GetVertexData(), hp_Bar_Geometry_Frame->GetVertexCount() * sizeof(VertexPositionScaleSprite));
			hp_Bar_InstanceBuffer_Frame->SetVertexCount(hp_Bar_Geometry_Frame->GetVertexCount());
		}
		hp_Bar_InstanceBuffer_Frame->Unmap();

		vdata = hp_Bar_InstanceBuffer_Gauge->Map<VertexPositionScaleSprite>();
		{
			memcpy(vdata, hp_Bar_Geometry_Gauge->GetVertexData(), hp_Bar_Geometry_Gauge->GetVertexCount() * sizeof(VertexPositionScaleSprite));
			hp_Bar_InstanceBuffer_Gauge->SetVertexCount(hp_Bar_Geometry_Gauge->GetVertexCount());
		}
		hp_Bar_InstanceBuffer_Gauge->Unmap();
	}

}

void MonsterManager::Update_LevelUpEffect()
{
	for (auto effect : effects_map[MonsterEffectType::LevelUp])
		effect->Update();
}

void MonsterManager::Update_Dropped_Item()
{
	for (auto effect : effects_map[MonsterEffectType::Dropped_Item])
	{
		if (effect->IsActive())
		{
			effect->GetComponent<RigidBody>()->Jump(Vector3(0, 2.0f, 0.0f));
			effect->Update();
		}
	}
}

void MonsterManager::Update_SkillEffect()
{
	for (auto effect : effects_map[MonsterEffectType::Skill_Effect])
		effect->Update();
}

void MonsterManager::SetHP_Bar(ProgressBar* var)
{
	if (!var)
		return;

	hp_Bar = var;

	auto frames = hp_Bar->GetFrames();
	for (auto& frame : frames)
		frame->SetIsInstanced(true);
}

void MonsterManager::Resize_Skill_Effect()
{
	LOG_INFO("Total actors for skill is fall short");
	std::string tmp_path = "//characters//slime//stand_info.txt";

	auto& actorsForSkill = effects_map[MonsterEffectType::Skill_Effect];
	actorsForSkill.reserve(actorsForSkill.size() + 10);
	for (int i = 0; i < 10; i++)
	{
		Actor* actor = new Actor(context);
		Renderable* renderable = actor->AddComponent<Renderable>();
		actor->AddComponent<RigidBody>();
		actor->AddComponent<Transform>();
		actor->AddComponent<Controller>();
		renderable->SetMaterial("Ex.material");
		renderable->SetMesh("QUAD.mesh");
		Animator* animator = actor->AddComponent<Animator>();
		animator->SetAnimation(tmp_path, "slime stand", renderable);
		actor->SetName("Skill " + std::to_string(i));
		actor->SetActive(false);
		actor->Update();
		actorsForSkill.emplace_back(actor);
	}
}
