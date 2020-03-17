#pragma once
#include "pch.h"

class Data_Dialog : public IData
{
public:
	Data_Dialog(const std::string& name)
	{
		SetType(DataType::Dialog);
		SetName(name);
	}
	~Data_Dialog() = default;

	void SaveToFile(const std::string& path);
	void LoadFromFile(const std::string& path);

public:
	void SetDialogScriptPath(const std::string& path) { _dialogScriptPath = path; }
	const std::string& GetDialogScriptPath() { return  _dialogScriptPath; }

public:
	std::string _dialogScriptPath = "UI/Dialog/NaoZoneMorian_Frame.as";
	int _state = 0; // dialog state 
};