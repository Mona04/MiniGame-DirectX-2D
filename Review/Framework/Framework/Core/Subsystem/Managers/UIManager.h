#pragma once
#include "../ISubsystem.h"

class UIManager final : public ISubsystem
{
public:
	static std::string defaultDir;

public:
	UIManager(class Context* context);
	~UIManager();

	const bool Initialize() override;
	void Update();

	void ClearUIes();

	class UI* GetCurrentUI() const { return currentUI; }
	void SetCurrentUI(const std::string& name);

	class UI* GetCurrentPreUI() const { return currentPreUI; }
	void SetCurrentPreUI(const std::string& name);

	std::map<std::string, class UI*>& GetUIes() { return UIes; }
	std::map<std::string, class UI*>& GetPreUIes() { return preUIes; }

	void CreateUI(const std::string& name);
	void LoadUI(const std::string& path);
	void LoadPreUI(const std::string& path);

	void SaveUI(const std::string& path, const std::string& name);

	class Box* GetUIComponent_Box(const std::string& name);
	class ProgressBar* GetUIComponent_ProgressBar(const std::string& name);

private:
	class UI* currentUI;
	class UI* currentPreUI;

	std::map<std::string, class UI*> UIes;
	std::map<std::string, class UI*> preUIes;
};