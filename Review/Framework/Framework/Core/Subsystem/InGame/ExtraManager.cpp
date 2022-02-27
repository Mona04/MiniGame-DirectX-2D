#include "Framework.h"
#include "ExtraManager.h"

ExtraManager::ExtraManager(Context* context)
	: ISubsystem(context)
{
	EventSystem::Get()->Subscribe(EventType::Update, EVENT_HANDLER(Update));

	uiManager = context->GetSubsystem<UIManager>();
	sceneManager = context->GetSubsystem<SceneManager>();
	dataManager = context->GetSubsystem<DataManager>();
	dialogManager = context->GetSubsystem<DialogManager>();
	inventoryManager = context->GetSubsystem<InventoryManager>();
	thread = context->GetSubsystem<Thread>();
	resourceManager = context->GetSubsystem<ResourceManager>();
	monsterManager = context->GetSubsystem<MonsterManager>();
	mouseManager = context->GetSubsystem<MouseManager>();
}

ExtraManager::~ExtraManager()
{
}

void ExtraManager::Clear()
{
	mainGame = nullptr;
	hp_Bar = nullptr;
	mp_Bar = nullptr;
	sp_Bar = nullptr;
	exp_Bar = nullptr;
	menuButton = nullptr;
	verticalList = nullptr;
	saveLoad = nullptr;
	protagonist_controller = nullptr;
}

const bool ExtraManager::Initialize()
{
	return true;
}

void ExtraManager::Update()
{
	Update_MainGame();
}

void ExtraManager::UpdateSaveLoad()
{
	saveLoad->UpdateSlots();
}

void ExtraManager::Update_MainGame()  // Script 로 빼야하는데 ....
{
	if (Synchronization_MainGame())
	{
		if(hp_Bar) hp_Bar->SetProgress(protagonist_controller->GetHP(), protagonist_controller->GetMaxHP());
		if(mp_Bar) mp_Bar->SetProgress(protagonist_controller->GetMP(), protagonist_controller->GetMaxMP());
		if(sp_Bar) sp_Bar->SetProgress(protagonist_controller->GetSP(), protagonist_controller->GetMaxSP());
		if(exp_Bar) exp_Bar->SetProgress(protagonist_controller->GetExp(), protagonist_controller->GetMaxExp());
		if (menuButton)
		{
			if (menuButton->IsClicked())
				verticalList->SetIsVisible(!verticalList->GetIsVisible());
		}
		if (verticalList && verticalList->GetIsVisible())
		{
			if (verticalList->GetFrames()[6]->IsClicked())
			{
				if (saveLoad->GetIsVisible())
					saveLoad->SetIsVisible(false);
				else
				{
					saveLoad->SetIsVisible(true);
					saveLoad->UpdateSlots();
				}
			}

			if (mouseManager->IsClicked() && verticalList->GetFrames()[0]->IsCovered() == false)				
				verticalList->SetIsVisible(false);
		}
	}
}

bool ExtraManager::Synchronization_MainGame()
{
	if (uiManager->GetCurrentUI()->GetName() != "MainGame")
		return false;

	if (mainGame == nullptr)
	{
		mainGame = uiManager->GetUIes()["MainGame"];

		if (mainGame == nullptr)
			return false;

		hp_Bar = mainGame->GetComponent<ProgressBar>("HP_Bar");
		mp_Bar = mainGame->GetComponent<ProgressBar>("MP_Bar");
		sp_Bar = mainGame->GetComponent<ProgressBar>("SP_Bar");
		exp_Bar = mainGame->GetComponent<ProgressBar>("Exp_Bar");
		menuButton = mainGame->GetComponent<Box>("MenuButton");
		verticalList = mainGame->GetComponent<VerticalList>("VerticalList");
		saveLoad = mainGame->GetComponent<SaveLoad>("SaveLoad");
	}

	if(protagonist_controller == nullptr)
		protagonist_controller = context->GetSubsystem<GameManager>()->GetProtagonistController();

	if (protagonist_controller == nullptr)
		return false;

	return true;
}
