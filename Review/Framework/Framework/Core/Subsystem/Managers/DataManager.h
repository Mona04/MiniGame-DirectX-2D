#pragma once
#include "../ISubsystem.h"

struct INVEN_COORD
{
	INVEN_COORD(const int& x, const int& y) : x(x), y(y) {}
	INVEN_COORD(const INVEN_COORD& ls) : x(ls.x), y(ls.y) {}
	int x; int y;
};

struct Data_Mob_Cap
{
	Data_Mob_Cap() : data(nullptr) {};
	Data_Mob_Cap(Data_Mob* mob) : data(mob) {}

	bool operator==(const Data_Mob_Cap& rs) { return rs.data->GetName() == data->GetName(); }

	Data_Mob* data;
};

struct Evolution_Condition
{
	Evolution_Condition() : lv(-1), item_fire(-1), item_water(-1), item_light(-1), item_dark(-1) {}
	Evolution_Condition(const int& lv, const int& fire, const int& water, const int& light, const int& dark)
		: lv(lv), item_fire(fire), item_water(water), item_light(light), item_dark(dark) {}

	int lv;
	int item_fire;
	int item_water;
	int item_light;
	int item_dark;
};

class DataManager final : public ISubsystem
{
public:
	DataManager(class Context* context);
	~DataManager();

	const bool Initialize() override;
	void Update();

	std::vector<BlockKind> GetBlockKinds() { return blockKinds; }
	BlockKind GetRandomBlockKind(const int& region, const int& type);
	std::string GetDirectory(const DataType& type) { return directories[type]; }
	std::map<DataType, std::map<std::string, class IData*>>& GetDatasMap() { return datasMap; }
	std::map<std::string, class IData*>& GetDatas(const DataType& type) { return datasMap[type]; }
	template<typename T> T* GetData(const std::string& name);

	Data_Item* GetItemData(const int& code);
	class Tree<Data_Mob_Cap, Evolution_Condition>* GetEvolutionTree() { return evolutionTree; }

	void CreateDefault(const DataType& type, const std::string& name = "tmp");
	void SaveDatas();

private:
	void Init_Directories();
	void Init_BlockKinds();
	void Init_DatasMap();
	void Init_EvolutionTree();

	void Update_Mobs();
	void Update_Skills();
	void Update_Items();
	void Update_Inventorys();
	void Update_Field();
	void Update_Portal();
	void Update_Spawn();

public:
	void Init_Default(const std::string& name, const int& width, const int& height);
	void Init_Plain(const std::string& name, const int& width, const int& height, const int& min, const int& max);
	void Init_SkyStairWay(const std::string& name, const int& width, const int& height, const int& min_height, const int& max_height, const int& suc);
	void Make_SkyIsland(const std::string& name, const int& width, const int& height, const int& point_x, const int& point_y, const int& island_width);
	void Init_Ect(const std::string& name, const int& width, const int& height);

	const bool IsConcave(const std::string& name, const int& width, const int& height, const int& point_x, const int& point_y);

public:
	static Vector3 BlockLocToBlockPos(const int& width, const int& height, const int& x, const int& y);
	static std::pair<int, int> BlockPosToBlockLoc(const int& width, const int& height, const Vector3& pos);

private:
	std::vector<DataType> dataTypes;
	std::map<DataType, std::string> directories;
	std::vector<BlockKind> blockKinds;
	std::map<DataType, std::map<std::string, class IData*>> datasMap;

	std::map<std::string, std::pair<std::pair<int, int>, IData*>> inventoryDatas;

	class Tree<Data_Mob_Cap, Evolution_Condition>* evolutionTree;
};

template<typename T>
inline T* DataManager::GetData(const std::string& name)
{
	if (name == "N\A") return nullptr;

	DataType type = IData::DeduceDataType<T>();
	if (datasMap[type].find(name) != datasMap[type].end())
		return static_cast<T*>(datasMap[type][name]);
	else nullptr;
};