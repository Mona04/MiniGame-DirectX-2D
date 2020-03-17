#pragma once
#include "pch.h"

enum class DataType : uint
{
	Unknown,
	Mob,
	Skill,
	Field,
	Portal,
	Dialog,
	Spawn,
	Town,
	item,
	Inventory,
	Save,
};

class IData
{
public:
	const DataType& GetType() { return type; }
	void SetType(const DataType& var) { type = var; }

	const std::string& GetName() { return name; }
	void SetName(const std::string& var) { name = var; }

	virtual void SaveToFile(const std::string& path) = 0;
	virtual void LoadFromFile(const std::string& path) = 0;

private:
	DataType type;
	std::string name;
};