#pragma once
#include "../ISubsystem.h"

class DialogManager final : public ISubsystem
{
public:
	DialogManager(class Context* context);
	~DialogManager();

	const bool Initialize() override;
	void Update();

	void Clear();

public:
	void DialogDefaultUpdate();
	void DialogSetIllust(const std::string& path);
	void DialogSetName(const std::string& content);
	void DialogSetText(const std::string& content);
	void DialogSetButton(int index, const std::string& name);
	bool IsDialogButtonClicked(int index);
	void DialogSetScript(const std::string& path, Data_Dialog* dialogData = nullptr);
	void DialogEnd();
	int DialogGetState() { if (dialogData) return dialogData->_state; else return 0; }
	void DialogSetState(int var) { if(dialogData) dialogData->_state = var;}  // Usually used by Controller 

private:
	class UIManager* uiManager;
	class UI* dialogUI;
	class Box* script;
	class Box* illust;
	class Box* name;
	class Box* text;
	std::vector<class Box*> buttons;
	std::vector<class Box*> buttonTexts;
	Data_Dialog* dialogData = nullptr;

	int _state = 0;
};