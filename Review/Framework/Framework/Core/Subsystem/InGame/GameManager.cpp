#include "Framework.h"
#include "GameManager.h"
#include "Framework/Core/Engine.h"

#define NUM_FLOOR 16

GameManager::GameManager(Context* context)
	: ISubsystem(context)
{
	EventSystem::Get()->Subscribe(EventType::Default_Update, EVENT_HANDLER(Update));
}

GameManager::~GameManager()
{
	for(auto& saveData : saveDatas)
		SAFE_DELETE(saveData);

	Scene* currentScene = sceneManager->GetCurrentScene();
	if (!!currentScene)
		currentScene->RemoveActor(protagonist);

	SAFE_DELETE(protagonist);
}

const bool GameManager::Initialize()
{ 
	uiManager = context->GetSubsystem<UIManager>();
	sceneManager = context->GetSubsystem<SceneManager>();
	physicsManager = context->GetSubsystem<PhysicsManager>();
	dataManager = context->GetSubsystem<DataManager>();
	dialogManager = context->GetSubsystem<DialogManager>();
	inventoryManager = context->GetSubsystem<InventoryManager>();
	thread = context->GetSubsystem<Thread>();
	resourceManager = context->GetSubsystem<ResourceManager>();
	monsterManager = context->GetSubsystem<MonsterManager>();

	for (int slot = 0; slot < _maxSlot; slot++)
	{
		auto saveData = saveDatas.emplace_back(new Data_Save("SaveData" + std::to_string(slot)));
		saveData->LoadFromFile("../../_Assets/Data/Save/" + GetSlotTag(slot) + "Save.data");
	}

	SetBgm("Bgm/Main.mp3");
	for (const auto& filePath : FileSystem::GetAllFilesInDirectory("../../_Assets/Audio/Effect/"))
		resourceManager->Load<AudioClip>(filePath, filePath);

	protagonist = new Actor(context);
	protagonist->LoadFromFile("../../_Assets/Scene/Protagonist/Protagonist.actor");
	protagonist->SetIsCameraAttached(true);
	protagonist->SetName("Protagonist");

	if (context->GetEngine()->IsOnEngineFlags(EngineFlags::ENGINEFLAGS_GAME))
	{
		uiManager->LoadUI("MainMenu.ui");
		uiManager->SetCurrentUI("MainMenu");
	}

	return true;
}

void GameManager::Update()
{
	GameOver();
	Gradiate();

	//if (context->GetSubsystem<Input>()->KeyDown(KeyCode::KEY_CONTROL))
	//{
	//	static int i = 1;
	//	monsterManager->Teleport("Floor" + std::to_string(i++), protagonist->GetName(), Vector3(0, 0, 0));
	//}
}

void GameManager::MainMenu_Start()
{
	_slot = 0;
	auto save = GetSaveData(0);
	save->_mapName = "NaoZone";
	save->_protagonist_mobData = "ThePepe";
	save->_slot = 0;
	protagonist->GetComponent<Controller>()->Evolution(save->_protagonist_mobData);
	protagonist->GetComponent<Controller>()->Teleport(Vector3(0, 0, -10));

	dataManager->CreateDefault(DataType::Inventory, GetSlotTag(saveDatas[_slot]->_slot) + "Inventory");   // make inventory
	dataManager->GetData<Data_Dialog>("NaoZone_Morian")->_state = 0;

	Init_Dialog();
	GamePrepare();
}

void GameManager::MainMenu_Exit()
{
	context->GetEngine()->Destroy();
}

void GameManager::LoadGame(int slot)
{
	_slot = slot;
	_mainMenu_Stack = 0;

	auto save = GetSaveData(slot);
	if (save == nullptr)
	{
		MainMenu_Start();
		return;
	}

	protagonist->GetComponent<Controller>()->Evolution(save->_protagonist_mobData);  // it should be done first as evolution reset lv, factor 
	protagonist->GetComponent<Controller>()->SetLv(save->_lv);
	protagonist->GetComponent<Controller>()->SetJumpFactor(save->_jumpFactor);
	protagonist->GetComponent<Controller>()->SetSpeedFactor(save->_speedFactor);
	auto dialogs = FileSystem::GetAllFilesInDirectory("../../_Assets/Data/Dialog/");
	int i = 0;
	for (const auto& dialog : dialogs)
	{
		auto a = dataManager->GetData<Data_Dialog>(FileSystem::GetIntactFileNameFromPath(dialog));
		dataManager->GetData<Data_Dialog>(FileSystem::GetIntactFileNameFromPath(dialog))->_state = save->_npcs[i++];
	}
	auto tmp = context->GetSubsystem<DataManager>()->GetDatas(DataType::Inventory)[GetSlotTag(slot) + "Inventory"];
	if (tmp)
		tmp->LoadFromFile("../../_Assets/Data/Inventory/" + GetSlotTag(slot) + "Inventory" + ".data");

	if(save->_mapName == "NaoZone")  
		protagonist->GetComponent<Controller>()->Teleport(Vector3(0, 0, -10));
	else
		protagonist->GetComponent<Controller>()->Teleport(Vector3(0, -3000.0f, -10));

	GamePrepare();
}

void GameManager::SaveGame(int slot)
{
	if (slot >= _maxSlot) return;

	auto saveData = saveDatas[slot];
	saveData->_mapName = sceneManager->GetCurrentScene()->GetName();
	saveData->_slot = this->_slot;
	saveData->_protagonist_mobData = protagonist->GetComponent<Controller>()->GetMobData()->GetName();
	saveData->_lv = protagonist->GetComponent<Controller>()->GetLv();
	saveData->_speedFactor = protagonist->GetComponent<Controller>()->GetSpeedFactor();
	saveData->_jumpFactor = protagonist->GetComponent<Controller>()->GetJumpFactor();
	saveData->_npcs.resize(5 * NUM_FLOOR);

	auto dialogs = FileSystem::GetAllFilesInDirectory("../../_Assets/Data/Dialog/");
	int i = 0;
	for (const auto& dialog : dialogs)	
		saveData->_npcs[i++] = dataManager->GetData<Data_Dialog>(FileSystem::GetIntactFileNameFromPath(dialog))->_state;
	saveData->SaveToFile("../../_Assets/Data/Save/" + GetSlotTag(slot) + "Save.data");	

	auto inventoryData = inventoryManager->GetInventoryData();
	inventoryData->SaveToFile("../../_Assets/Data/Inventory/" + GetSlotTag(slot) + "Inventory" + ".data");
	auto tmp = context->GetSubsystem<DataManager>()->GetDatas(DataType::Inventory)[GetSlotTag(slot) + "Inventory"]; 
	if(!tmp)
		context->GetSubsystem<DataManager>()->GetDatas(DataType::Inventory)[GetSlotTag(slot) + "Inventory"] = inventoryData;

	context->GetSubsystem<ExtraManager>()->UpdateSaveLoad();
}

void GameManager::MainMenu_LoadReady()
{
	auto ui = uiManager->GetUIes()["MainMenu.ui"];
	ui->GetComponent<Box>("button_start")->GetFirstFrame()->SetText(L"Slot 1");
}

void GameManager::NormalEnding()
{
	SetBgm("Bgm/NormalEnding.mp3");
	uiManager->SetCurrentUI("Dialogs");
	auto backGround = uiManager->GetCurrentUI()->GetComponent<Box>("BackGround");
	backGround->SetIsVisible(true);
	backGround->GetFirstFrame()->GetRenderable()->SetTexture(TextureType::Albedo, "../../_Assets/Texture/UI/NormalEnding.png", "../../_Assets/Texture/UI/NormalEnding.png");
	dialogManager->DialogSetScript("../../_Assets/Script/Dialog/NormalEnding_Frame.as");  // you don't insert data_dialog as it is mine not others
}

void GameManager::TrueEnding()
{
	SetBgm("Bgm/TrueEnding.mp3");
	uiManager->SetCurrentUI("Dialogs");
	auto backGround = uiManager->GetCurrentUI()->GetComponent<Box>("BackGround");
	backGround->SetIsVisible(true);
	backGround->GetFirstFrame()->GetRenderable()->SetTexture(TextureType::Albedo, "../../_Assets/Texture/UI/TrueEnding.png", "../../_Assets/Texture/UI/TrueEnding.png");
	dialogManager->DialogSetScript("../../_Assets/Script/Dialog/TrueEnding_Frame.as");  // you don't insert data_dialog as it is mine not others
}

void GameManager::GamePrepare()
{
	if (ProgressReport::Get()->GetIsLoadingOfReport(ProgressReport::Scene) == true)
		return;

	uiManager->LoadPreUI("Loading.ui");
	uiManager->SetCurrentPreUI("Loading");
	ProgressBar* bar = context->GetSubsystem<UIManager>()->GetCurrentPreUI()->GetComponent<ProgressBar>();

	// 이걸로 자동 맵생성 할건지 아닐지 결정함. 근데 오래걸려서 첨에 맵 생성용으로만 썼음.
	int total_floor = 0;

	thread->AddTask([this, bar, total_floor]()
		{
			{
				ProgressReport* reporter = ProgressReport::Get();
				reporter->SetDefault(ProgressReport::Scene, 6 + total_floor, uiManager->GetCurrentPreUI()->GetComponent<ProgressBar>());

				GetProtagonistController()->SetProtagonist(true);
				protagonist->SetActive(true);
				reporter->OneStepForward(ProgressReport::Scene);

				uiManager->LoadUI("GameOver.ui");
				uiManager->LoadUI("NormalEnding.ui");
				uiManager->LoadUI("TrueEnding.ui");
				uiManager->LoadUI("MainGame.ui");
				reporter->OneStepForward(ProgressReport::Scene);

				inventoryManager->SetInventory(uiManager->GetUIes()["MainGame"]->GetComponent<Inventory>("Inventory"));
				inventoryManager->SetInventoryData(GetSlotTag(saveDatas[_slot]->_slot) + "Inventory");
				reporter->OneStepForward(ProgressReport::Scene);

				std::string mapName = GetSaveData(_slot)->_mapName;
				sceneManager->LoadScene(mapName + ".scene"); // Before Initialize Scene Resources must be loaded
				sceneManager->GetScenes()[mapName]->AddActor(protagonist); // before Intialize MainGame.ui NaoZone should be Loaded;
				sceneManager->SetCurrentScene(mapName);
				SetBgm(sceneManager->GetScenes()[mapName]->GetDataField()->_bgmPath);
				reporter->OneStepForward(ProgressReport::Scene);

				monsterManager->SetSpawnList(dataManager->GetData<Data_Spawn>(GetSaveData(_slot)->_mapName));
				reporter->OneStepForward(ProgressReport::Scene);

				resourceManager->Set_TemperateMode(true);
				{
					if (total_floor > 0)
					{
						std::string name;
						for (int i = 1; i < total_floor; i++)
						{
							name = "Floor" + std::to_string(i);
							Scene* scene = sceneManager->MakeScene(name);
							{
								Data_Field* fieldData = new Data_Field(name);
								fieldData->Init_Region(i);
								dataManager->GetDatas(DataType::Field)[name] = fieldData;

								Data_Spawn* spawnData = new Data_Spawn(name);
								spawnData->Init_MobList(i);
								dataManager->GetDatas(DataType::Spawn)[name] = spawnData;

								dataManager->Init_Default(name, 500, 500);
								dataManager->Init_Plain(name, 500, 500, 10, 18);
								dataManager->Init_SkyStairWay(name, 500, 500, 10, 18, 4);
								dataManager->Init_Ect(name, 500, 500);

								scene->SetDataField(dataManager->GetData<Data_Field>(name), i);
								scene->SetDataSpawn(dataManager->GetData<Data_Spawn>(name));
							}
							sceneManager->SaveScene(scene); SAFE_DELETE(scene);
							reporter->OneStepForward(ProgressReport::Scene);
						}
						dataManager->SaveDatas();
					}
				}
				resourceManager->Set_TemperateMode(false);

				reporter->OneStepForward(ProgressReport::Scene);

				while (thread->LeftJobs() > 1)
					Sleep(500.0f);

				if (GetSaveData(_slot)->_mapName == "NaoZone")
				{
					uiManager->SetCurrentUI("Dialogs");
					dialogManager->DialogSetScript("Dialog/NaoZone_Frame.as");
				}
				else
				{
					uiManager->SetCurrentUI("MainGame");
				}

				reporter->OneStepForward(ProgressReport::Scene);
			}
			context->GetEngine()->OnEngineFlags(EngineFlags::ENGINEFLAGS_PLAY);
		}
	);
}

void GameManager::GameOver()
{
	Controller* pro_con = GetProtagonistController();
	if (!pro_con) return;
	if (pro_con->GetHP() > 0) return;

	if (uiManager->GetCurrentUI()->GetName() != "GameOver")
	{
		SetBgm("Bgm/Main.mp3");
		uiManager->SetCurrentUI("GameOver");
		_gradiate_limitTime = 3000.0f;
	}
}

void GameManager::LoadResource()
{
	auto filepaths = FileSystem::GetAllFilesInDirectory("../../_Assets/Texture");
	for (auto filepath : filepaths)
	{
		resourceManager->Load<Texture>(filepath, filepath);
	}	
}

void GameManager::BackToMainMenu()
{
	if (context->GetSubsystem<SceneManager>()->GetCurrentScene() == nullptr)
		return;

	uiManager->GetUIes()["Dialogs"]->GetComponent<Box>("BackGround")->SetIsVisible(false);
	context->GetSubsystem<SceneManager>()->GetCurrentScene()->DeleteActor(protagonist->GetName());
	
	context->GetSubsystem<InventoryManager>()->Clear();
	context->GetSubsystem<MonsterManager>()->Clear_();
	context->GetSubsystem<ExtraManager>()->Clear();
	context->GetSubsystem<Renderer>()->Clear_();
	context->GetSubsystem<PhysicsManager>()->Clear();
	context->GetSubsystem<SceneManager>()->ClearScenes();

	uiManager->LoadUI("MainMenu.ui");
	uiManager->SetCurrentUI("MainMenu");

	_mainMenu_Stack = 0;

	GetProtagonistController()->TmpGauge();
	protagonist->SetActive(true);
}

void GameManager::Init_Dialog()
{
	std::vector<std::string> npcs = {"Morian", "Cichol", "Blony", "Fleta"};
	for(const auto& npc : npcs)
		for (int i = 1; i < 17; i++)
		{
			auto dataName = "Floor" + std::to_string(i) + npc + "_Frame"; // "Floor1Morian_Frame.as"
			dataManager->GetData<Data_Dialog>(dataName)->_state = 0;
		}
}

void GameManager::Gradiate()
{
	static int _state = 0;
	static float _accumulatedTime = 0.0f;

	if(_gradiate_limitTime > 0.0f)
	{
		Material* _material = context->GetEngine()->GetFrame()->GetRenderable()->GetMaterial();

		switch (_state)
		{
		case 0:
		{
			_material->SetAlbedoColor(Color4(0.5, 0.5, 0.5, 0.5f));
			_state = 1;
			break;
		}
		case 1:
		{
			if (_material->GetAlbedoColor().r < 10.0f)
				_material->SetAlbedoColor(_material->GetAlbedoColor() + Color4(0.4, 0.4, 0.4, 0.4f));
			else if (_material->GetAlbedoColor().r > 2.0f)
				_state = 2;
			break;
		}
		case 2:
		{
			if (_material->GetAlbedoColor().r > 1.01f)
				_material->SetAlbedoColor(_material->GetAlbedoColor() - Color4(0.1, 0.1, 0.1, 0.1f));
			else
				_state = 3;
			break;
		}
		case 3:
		{
			if (_accumulatedTime <= _gradiate_limitTime)
				_accumulatedTime += context->GetSubsystem<Timer>()->GetDeltaTimeMs();
			else
				_state = 4;
			break;
		}
		case 4:
		{
			_state = 0;
			_accumulatedTime = 0;
			_gradiate_limitTime = 0;
			BackToMainMenu();
			uiManager->GetUIes()["Dialogs"]->GetComponent<Box>("BackGround")->SetIsVisible(false);
			break;
		}
		}
	}
}

Controller* GameManager::GetProtagonistController()
{
	return protagonist ? protagonist->GetComponent<Controller>() : nullptr;
}

std::string GameManager::GetProtagonistLv()
{
	Controller* tmp = GetProtagonistController();
	if (tmp) return std::to_string(tmp->GetLv()); 
	else return std::string("0"); 
}

std::string GameManager::GetProtagonistMobName()
{
	Controller* tmp = GetProtagonistController();
	if (tmp) return tmp->GetMobData()->_mobName;
	else return "N\A";
}

void GameManager::EnforceProtagonistJump()
{
	GetProtagonistController()->SetJumpFactor(GetProtagonistController()->GetJumpFactor() + 1);
}

void GameManager::EnforceProtagonistSpeed()
{
	GetProtagonistController()->SetSpeedFactor(GetProtagonistController()->GetSpeedFactor() + 1);
}

void GameManager::SetBgm(const std::string& path)
{
	if(bgm)
		bgm->Stop();

	bgm = resourceManager->Load<AudioClip>(path, path);
	bgm->SetLoop(true);
	bgm->Play();
	bgm->SetVolume(bgm_volume);
}


