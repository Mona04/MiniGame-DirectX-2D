#include "Framework.h"
#include "UIManager.h"
#include "Framework/UI/UI.h"

std::string UIManager::defaultDir = "../../_Assets/UI/";


UIManager::UIManager(Context* context)
	: ISubsystem(context)
	, currentUI(nullptr)
	, currentPreUI(nullptr)
{
	EventSystem::Get()->Subscribe(EventType::Default_Update, EVENT_HANDLER(Update));
}

UIManager::~UIManager()
{
	currentUI = nullptr;
	currentPreUI = nullptr;

	for (auto ui : preUIes)
		SAFE_DELETE(ui.second);

	for (auto ui : UIes)
		SAFE_DELETE(ui.second);

	UIes.clear();
	preUIes.clear();

}

const bool UIManager::Initialize()
{
	for (const auto& ui : UIes)
		ui.second->Init();

	for (const auto& preui : preUIes)
		preui.second->Init();

	return true;
}

void UIManager::Update()
{
	if(currentUI && !ProgressReport::Get()->GetIsLoadingOfReport(ProgressReport::Scene))
		currentUI->Update();
	if (currentPreUI)
		currentPreUI->Update();
}

void UIManager::ClearUIes()
{
	for (auto ui : UIes)
		SAFE_DELETE(ui.second);

	UIes.clear();
}

void UIManager::SetCurrentUI(const std::string& _name)
{
	std::string name = FileSystem::GetIntactFileNameFromPath(_name);
	if (UIes.count(name) <= 0)
	{
		LOG_ERROR("There is no UI with name %s", name.data());
		return;
	}
	currentUI = UIes[name];
	context->GetSubsystem<Renderer>()->AcquireUI(currentUI);
}

void UIManager::SetCurrentPreUI(const std::string& name)
{
	if (preUIes.count(name) <= 0)
	{
		LOG_ERROR("There is no PreUI with name %s", name.data());
		return;
	}
	currentPreUI = preUIes[name];
	context->GetSubsystem<Renderer>()->AcquirePreUI(currentPreUI);
}

void UIManager::CreateUI(const std::string& name)
{
	UI* ui = new UI(context);
	ui->SetName(name);
	UIes[name] = ui;
}

void UIManager::LoadUI(const std::string& path)
{
	std::string name = FileSystem::GetIntactFileNameFromPath(path);
	if (UIes.count(name) > 0)
	{
		LOG_INFO("UI with same name exist");
		SAFE_DELETE(UIes[name]);
	}
	UI* ui = new UI(context);
	ui->LoadFromFile(defaultDir + path);
	ui->SetName(name);
	UIes[name] = ui;
}

void UIManager::LoadPreUI(const std::string& path)
{
	std::string name = FileSystem::GetIntactFileNameFromPath(path);
	if (preUIes.count(name) > 0)
	{
		LOG_ERROR("UI with same name exist");
		SAFE_DELETE(preUIes[name]);
	}
	UI* ui = new UI(context);
	ui->LoadFromFile(defaultDir + path);
	ui->SetName(name);
	preUIes[name] = ui;
}

void UIManager::SaveUI(const std::string& path, const std::string& name)
{
	if (UIes.count(name) <= 0)
	{
		LOG_ERROR("UI with same name do not exist");
		return;
	}
	UIes[name]->SaveToFile(defaultDir + path);
}

Box* UIManager::GetUIComponent_Box(const std::string& name)
{
	 return (currentUI->GetComponent<Box>(name)); 
}

ProgressBar* UIManager::GetUIComponent_ProgressBar(const std::string& name)
{
	return (currentUI->GetComponent<ProgressBar>(name));
}
