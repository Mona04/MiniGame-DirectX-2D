#include "Framework.h"
#include "GameManager.h"
#include "Framework/Core/Engine.h"

DialogManager::DialogManager(Context* context)
	: ISubsystem(context)

{
	EventSystem::Get()->Subscribe(EventType::Default_Update, EVENT_HANDLER(Update));

	uiManager = context->GetSubsystem<UIManager>();
}

DialogManager::~DialogManager()
{
}

const bool DialogManager::Initialize()
{
	Clear();

	uiManager->LoadUI("Dialogs.ui");
	dialogUI = uiManager->GetUIes()["Dialogs"];

	script = dialogUI->GetComponent<Box>("Script");
	illust = dialogUI->GetComponent<Box>("Illust");
	name = dialogUI->GetComponent<Box>("Name");
	text = dialogUI->GetComponent<Box>("Text");
	buttons.emplace_back(dialogUI->GetComponent<Box>("Button_1"));
	buttons.emplace_back(dialogUI->GetComponent<Box>("Button_2"));
	buttons.emplace_back(dialogUI->GetComponent<Box>("Button_3"));
	buttonTexts.emplace_back(dialogUI->GetComponent<Box>("Button_text_1"));
	buttonTexts.emplace_back(dialogUI->GetComponent<Box>("Button_text_2"));
	buttonTexts.emplace_back(dialogUI->GetComponent<Box>("Button_text_3"));

	return true;
}

void DialogManager::Update()
{

}

void DialogManager::Clear()
{
	dialogUI = nullptr;

	buttons.clear();
	buttons.shrink_to_fit();
	buttonTexts.clear();
	buttonTexts.shrink_to_fit();

	script = nullptr;
	illust = nullptr;
	name = nullptr;
	text = nullptr;
}

void DialogManager::DialogDefaultUpdate()
{
	Engine::Get()->OffEngineFlags(EngineFlags::ENGINEFLAGS_PLAY);

	for (auto& button : buttons)
		button->SetIsVisible(false);
	for (auto& buttonText : buttonTexts)
		buttonText->SetIsVisible(false);
	illust->SetIsVisible(false);
	name->SetIsVisible(false);
	text->SetIsVisible(false);

}

void DialogManager::DialogSetIllust(const std::string& path)
{
	illust->GetFrames()[0]->GetRenderable()->SetTexture(TextureType::Albedo, path, path);
	illust->SetIsVisible(true);
}

void DialogManager::DialogSetName(const std::string& content)
{
	name->GetFrames()[0]->SetTextFromMultibyte(content);
	name->SetIsVisible(true);
}

void DialogManager::DialogSetText(const std::string& content)
{
	text->GetFrames()[0]->SetTextFromMultibyte(content);
	text->SetIsVisible(true);
}

void DialogManager::DialogSetButton(int index, const std::string& name)
{
	if (index < 0 || index > 3)
		return;

	auto button = buttons[index];
	auto buttonText = buttonTexts[index];
	buttonText->GetFrames()[0]->SetTextFromMultibyte(name);
	buttonText->SetIsVisible(true);
	button->SetIsVisible(true);
}

bool DialogManager::IsDialogButtonClicked(int index)
{
	if (index < 0 || index > 3)
		return false;

	return buttons[index]->IsClicked();
}

void DialogManager::DialogSetScript(const std::string& path, Data_Dialog* dialogData)
{
	script->GetFrames()[0]->GetScripter()->SetScript(path, path, script->GetFrames()[0]);
	this->dialogData = dialogData;
}

void DialogManager::DialogEnd()
{
	DialogDefaultUpdate();
	Engine::Get()->OnEngineFlags(EngineFlags::ENGINEFLAGS_PLAY);
	uiManager->SetCurrentUI("MainGame");
}
