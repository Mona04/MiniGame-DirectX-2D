#pragma once
#include "Framework.h"

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

	const std::string GetName() const { return name; }
	void SetName(const std::string& var) { name = var; }
	
	virtual void SaveToFile(const std::string& path) = 0;
	virtual void LoadFromFile(const std::string& path) = 0;

	template<typename T> static DataType DeduceDataType();

private:
	DataType type;
	std::string name;
};

template<typename T>
inline DataType IData::DeduceDataType()
{
	std::string type = typeid(T).name();

	DataType enumType = DataType::Unknown;
	if (type.find("Data_Mob") != std::string::npos)				enumType = DataType::Mob;
	else if (type.find("Data_Skill") != std::string::npos)	enumType = DataType::Skill;
	else if (type.find("Data_Field") != std::string::npos)		enumType = DataType::Field;
	else if (type.find("Data_Portal") != std::string::npos)	enumType = DataType::Portal;
	else if (type.find("Data_Dialog") != std::string::npos)	enumType = DataType::Dialog;
	else if (type.find("Data_Spawn") != std::string::npos)		enumType = DataType::Spawn;
	else if (type.find("Data_Town") != std::string::npos)		enumType = DataType::Town;
	else if (type.find("Data_Item") != std::string::npos)		enumType = DataType::item;
	else if (type.find("Data_Inventory") != std::string::npos)		enumType = DataType::Inventory;

	return enumType;
}
