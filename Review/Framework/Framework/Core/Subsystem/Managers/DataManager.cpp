#include "Framework.h"
#include "DataManager.h"
#include "Framework/Data/IData.h"
#include "Framework/Data/Data_Mob.h"
#include "Framework/Data/Data_Item.h"
#include "Framework/Data/Data_Field.h"
#include "Framework/Data/Data_Portal.h"
#include "Framework/Data/Data_Town.h"
#include "Framework/Data/Data_Inventory.h"


DataManager::DataManager(Context* context)
	: ISubsystem(context)
{
	EventSystem::Get()->Subscribe(EventType::Update, EVENT_HANDLER(Update));
	dataTypes = { DataType::Mob, DataType::Skill, DataType::Field, DataType::Portal, DataType::Dialog,
		 DataType::Spawn, DataType::Town, DataType::item, DataType::Inventory };

}

DataManager::~DataManager()
{
	//SaveDatas();
	for (auto& datas : datasMap)
	{
		for (auto& data : datas.second)	
			SAFE_DELETE(data.second);
		datas.second.clear();
	}
	SAFE_DELETE(evolutionTree);
}

const bool DataManager::Initialize()
{
	Init_Directories();
	Init_BlockKinds();
	Init_DatasMap();
	Init_EvolutionTree();

	return true;
}

void DataManager::Update()
{
	Update_Mobs();
	Update_Skills();
	Update_Items();
	Update_Inventorys();
}

BlockKind DataManager::GetRandomBlockKind(const int& region, const int& type)
{
	std::vector<BlockKind> wannted;
	for (const auto& kind : blockKinds)
	{
		if ((kind % 1000) / 100 == type && (kind / 1000) == region)
			wannted.emplace_back(kind);
	}
	if (wannted.size() < 1) return 0;
	return wannted[Math::Random(0, wannted.size())];
}

Data_Item* DataManager::GetItemData(const int& code)
{
	Data_Item* result = nullptr;
	for(auto data : datasMap[DataType::item])
	{
		result = static_cast<Data_Item*>(data.second);
		if (result->_code == code)
			return result;
	}
	return nullptr;
}

void DataManager::CreateDefault(const DataType& type, const std::string& name)
{
	IData* tmp;
	switch (type)
	{
	case DataType::Mob: tmp = new Data_Mob(name); break;
	case DataType::Skill: tmp = new Data_Skill(name); break;
	case DataType::Portal: tmp = new Data_Portal(name); break;
	case DataType::Field: tmp = new Data_Field(name); break;
	case DataType::Dialog: tmp = new Data_Dialog(name); break;
	case DataType::Spawn: tmp = new Data_Spawn(name); break;
	case DataType::Town: tmp = new Data_Town(name); break;
	case DataType::item: tmp = new Data_Item(name); break;
	case DataType::Inventory: tmp = new Data_Inventory(name); break;
	default:
		tmp = new Data_Mob(name);
	}
	datasMap[type][name] = tmp;
	tmp->SaveToFile(GetDirectory(type) + name +".data");
}

void DataManager::SaveDatas()
{
	std::string directory;

	for (auto& datas : datasMap)
	{
		for (auto& data : datas.second)
		{
			//if (data.second->GetType() == DataType::Field)
			//	return;
			directory = GetDirectory(datas.first);
			data.second->SaveToFile(directory + data.second->GetName() + ".data");
		}
	}
}

void DataManager::Init_Directories()
{
	directories[DataType::Mob] = "../../_Assets/Data/Mob/";
	directories[DataType::Skill] = "../../_Assets/Data/Skill/";
	directories[DataType::Field] = "../../_Assets/Data/Field/";
	directories[DataType::Portal] = "../../_Assets/Data/Portal/";
	directories[DataType::Dialog] = "../../_Assets/Data/Dialog/";
	directories[DataType::Inventory] = "../../_Assets/Data/Inventory/";
	directories[DataType::item] = "../../_Assets/Data/item/";
	directories[DataType::Spawn] = "../../_Assets/Data/Spawn/";
	directories[DataType::Town] = "../../_Assets/Data/Town/";
}

void DataManager::Init_BlockKinds()
{
	FileStream stream;
	std::vector<std::string> filePaths = FileSystem::GetFilesInDirectory("../../_Assets/Scene/Blocks/");
	for (auto& path : filePaths)
		blockKinds.emplace_back(static_cast<BlockKind>(std::atoi(FileSystem::GetIntactFileNameFromPath(path).c_str())));
}

void DataManager::Init_DatasMap()
{
	std::string dataName;
	for (auto& type : dataTypes)
	{
		datasMap[type] = std::map<std::string, IData*>();
		if (type == DataType::Town) continue;
		auto filepaths = FileSystem::GetFilesInDirectory(GetDirectory(type));
		for (auto filepath : filepaths)
		{
			dataName = FileSystem::GetIntactFileNameFromPath(filepath);
			IData* data;
			switch (type)
			{
			case DataType::Mob: data = new Data_Mob(dataName); break;
			case DataType::Skill: data = new Data_Skill(dataName); break;
			case DataType::Field: data = new Data_Field(dataName); break;
			case DataType::Portal: data = new Data_Portal(dataName); break;
			case DataType::Dialog: data = new Data_Dialog(dataName); break;
			case DataType::Spawn: data = new Data_Spawn(dataName); break;
			case DataType::Town: data = new Data_Town(dataName); break;
			case DataType::item: data = new Data_Item(dataName); break;
			case DataType::Inventory: data = new Data_Inventory(dataName); break;
			default:
				data = new Data_Mob(dataName);
			}
			data->LoadFromFile(filepath);
			datasMap[type][dataName] = data;
		}
	}

}

void DataManager::Init_EvolutionTree()
{
	evolutionTree = new Tree<Data_Mob*>();
	std::vector<Data_Mob*> vertex_p = {
		GetData<Data_Mob>("snail"),             GetData<Data_Mob>("snail_blue"),            GetData<Data_Mob>("snail_red"),
		GetData<Data_Mob>("slime"),             GetData<Data_Mob>("mushroom_orange"),       GetData<Data_Mob>("stump"),
		GetData<Data_Mob>("slime_buble"),       GetData<Data_Mob>("slime_coke"),            GetData<Data_Mob>("sill_coke"),
		GetData<Data_Mob>("mushroom_blue"),     GetData<Data_Mob>("pig"),                   GetData<Data_Mob>("pig_ribon"),
		GetData<Data_Mob>("mushroom_coke"),     GetData<Data_Mob>("stump_dark"),            GetData<Data_Mob>("mask_wood"),
		GetData<Data_Mob>("slime_cube"),        GetData<Data_Mob>("mushroom_zombie"),       GetData<Data_Mob>("pig_wild"),
		GetData<Data_Mob>("pig_fire"),          GetData<Data_Mob>("eye_evil"),              GetData<Data_Mob>("eye_cuz"),
		GetData<Data_Mob>("mushroom_horn"),     GetData<Data_Mob>("lace_junior"),           GetData<Data_Mob>("octopus"),
		GetData<Data_Mob>("stump_axe"),         GetData<Data_Mob>("stump_darkaxe"),         GetData<Data_Mob>("mask_stone"),
		GetData<Data_Mob>("stoneball"),         GetData<Data_Mob>("sandrabbit"),            GetData<Data_Mob>("blockpus"),
		GetData<Data_Mob>("blockpus_king"),     GetData<Data_Mob>("sandrabbit_brown"),      GetData<Data_Mob>("mushroom_green"),
		GetData<Data_Mob>("raccoon_fire"),      GetData<Data_Mob>("eye_cold"),              GetData<Data_Mob>("catus_junior"),
		GetData<Data_Mob>("lace"),              GetData<Data_Mob>("matian"),                GetData<Data_Mob>("matian_pla"),
		GetData<Data_Mob>("catus"),             GetData<Data_Mob>("stoneball_fire"),        GetData<Data_Mob>("stoneball_ice"),
		GetData<Data_Mob>("cow"),               GetData<Data_Mob>("cow_bull"),              GetData<Data_Mob>("lantern"),
		GetData<Data_Mob>("sheep"),             GetData<Data_Mob>("sheep_black"),           GetData<Data_Mob>("cronos"),
		GetData<Data_Mob>("cronos_platoon"),    GetData<Data_Mob>("cronos_master"),         GetData<Data_Mob>("catus_loyal"),
		GetData<Data_Mob>("hobbyhorse"),        GetData<Data_Mob>("robo"),                  GetData<Data_Mob>("boogie_junior"),
		GetData<Data_Mob>("boogie"),            GetData<Data_Mob>("mute_iron"),             GetData<Data_Mob>("mute_mithril"),
		GetData<Data_Mob>("treelord"),          GetData<Data_Mob>("treelord_big"),          GetData<Data_Mob>("robo_master"),
		GetData<Data_Mob>("pixie_star"),        GetData<Data_Mob>("pixie_lunar"),           GetData<Data_Mob>("pixie_ghost"),
		GetData<Data_Mob>("firebomb"),          GetData<Data_Mob>("mute_enhanced_mithril"), GetData<Data_Mob>("pixie_lust"),
		GetData<Data_Mob>("gray_banad"),        GetData<Data_Mob>("gray_ultra"),            GetData<Data_Mob>("gruffin_junior"),
		GetData<Data_Mob>("sallion_junior"),    GetData<Data_Mob>("lioner_junior"),         GetData<Data_Mob>("bigeup"),
		GetData<Data_Mob>("buffy"),             GetData<Data_Mob>("buffy_razy"),            GetData<Data_Mob>("gruffin"),
		GetData<Data_Mob>("sallion"),           GetData<Data_Mob>("lioner"),                GetData<Data_Mob>("teddy_soul"),
		GetData<Data_Mob>("teddy_mastersoul"),  GetData<Data_Mob>("poonco"),                GetData<Data_Mob>("poosco"),
		GetData<Data_Mob>("luinel_junior"),     GetData<Data_Mob>("luinel"),                GetData<Data_Mob>("drake_capa"),
		GetData<Data_Mob>("drake"),             GetData<Data_Mob>("saity"),                 GetData<Data_Mob>("skeleton"),
		GetData<Data_Mob>("skeleton_officer"),  GetData<Data_Mob>("tiktok"),                GetData<Data_Mob>("drake_ice"),
		GetData<Data_Mob>("drake_red"),         GetData<Data_Mob>("drake_dark"),            GetData<Data_Mob>("skeleton_horse"),
		GetData<Data_Mob>("priest_oblivion"),   GetData<Data_Mob>("cago_wild"),             GetData<Data_Mob>("centaur_dark"),
		GetData<Data_Mob>("centaur_blue"),      GetData<Data_Mob>("wyvern_blue"),           GetData<Data_Mob>("wyvern_red"),
		GetData<Data_Mob>("wyvern_dark"),       GetData<Data_Mob>("priest_regret"),         GetData<Data_Mob>("half_blood"),
		GetData<Data_Mob>("tauromasis"),        GetData<Data_Mob>("taurospear"),            GetData<Data_Mob>("priest_recollection"),
		GetData<Data_Mob>("rich"),              GetData<Data_Mob>("clock"),                 GetData<Data_Mob>("clock_dark"),
		GetData<Data_Mob>("skelegon"),          GetData<Data_Mob>("skelos"),                GetData<Data_Mob>("pantomwatch"),
		GetData<Data_Mob>("viking"),            GetData<Data_Mob>("tanatos"), 
	};

	
	std::vector<std::pair<int, int>> edges = {
		std::pair(0, 1), std::pair(1, 2), std::pair(2, 3), std::pair(2, 4), std::pair(2, 5),
		std::pair(3, 6), std::pair(6, 7), std::pair(3, 12),std::pair(3, 8), std::pair(4, 9), std::pair(4, 10), std::pair(10, 11),std::pair(4, 12), std::pair(5, 13),std::pair(5, 14),
		std::pair(7, 15), std::pair(8, 11), std::pair(9, 28), std::pair(9, 16), std::pair(11, 17),  std::pair(17, 18),  std::pair(11, 19), std::pair(19, 20), std::pair(12, 16), std::pair(16, 21), std::pair(16, 22), std::pair(16, 23), std::pair(13, 24), std::pair(24, 25), std::pair(14, 26), std::pair(26, 27),
		std::pair(15, 29), std::pair(29, 30), std::pair(28, 31),  std::pair(18, 33),  std::pair(20, 34),  std::pair(20, 32), std::pair(21, 32),  std::pair(32, 35),  std::pair(22, 36),  std::pair(23, 37), std::pair(37, 38), std::pair(25, 35),  std::pair(35, 39),  std::pair(27, 40),  std::pair(27, 41),
		std::pair(30, 42), std::pair(42, 43), std::pair(31, 42), std::pair(33, 44), std::pair(34, 45), std::pair(45, 46), std::pair(36, 44), std::pair(38, 47), std::pair(47, 48), std::pair(48, 49),std::pair(39, 50), std::pair(40, 47), std::pair(41, 47),
		std::pair(43, 51), std::pair(51, 52),  std::pair(44, 53),  std::pair(53, 54),  std::pair(46, 55),  std::pair(55, 56),  std::pair(49, 53),  std::pair(50, 57), std::pair(57, 58),
		std::pair(52, 59),  std::pair(59, 60), std::pair(59, 61),  std::pair(59, 62),  std::pair(54, 63),  std::pair(56, 64),  std::pair(64, 62),  std::pair(58, 60),
		std::pair(60, 65),  std::pair(65, 66),  std::pair(66, 67),  std::pair(61, 68),  std::pair(68, 69),  std::pair(68, 70),  std::pair(62, 71), std::pair(63, 65),
		std::pair(67, 72),  std::pair(72, 73),  std::pair(68, 74),  std::pair(69, 75),  std::pair(70, 76),  std::pair(71, 77),  std::pair(77, 78),
		std::pair(73, 79),  std::pair(79, 80),  std::pair(74, 81), std::pair(74, 81), std::pair(75, 81), std::pair(76, 81), std::pair(81, 82),  std::pair(81, 83),  std::pair(83, 84), std::pair(78, 85), std::pair(85, 86), std::pair(86, 87),
		std::pair(80, 88), std::pair(84, 89),  std::pair(84, 90),  std::pair(84, 91),  std::pair(87, 92),  std::pair(87, 93),
		std::pair(88, 94), std::pair(82, 95),  std::pair(95, 96),  std::pair(89, 97),  std::pair(90, 98),  std::pair(91, 99), std::pair(87, 100),
		std::pair(94, 101), std::pair(96, 102),  std::pair(102, 103),  std::pair(97, 102),  std::pair(98, 102),  std::pair(99, 102), std::pair(92, 104),
		std::pair(92, 105), std::pair(93, 105),  std::pair(100, 105),  std::pair(104, 105),
		std::pair(101, 106), std::pair(106, 107),  std::pair(105, 108),  std::pair(108, 109),
		std::pair(107, 110), std::pair(103, 111),  std::pair(109, 112), 
	};
	evolutionTree->Init(vertex_p, edges);
}

void DataManager::Update_Mobs()
{
	//UI* curUI = context->GetSubsystem<UIManager>()->GetCurrentUI();
	//if (curUI)
	//{
	//	auto bar = curUI->GetComponent<ProgressBar>("MenuBar_HpBar");
	//	auto protagonistData = static_cast<Data_Mob*>(mobDatas["Protagonist"]);
	//	if (bar)
	//		bar->SetProgress(protagonistData->_hp, protagonistData->_maxHp);
	//}
}

void DataManager::Update_Skills()
{
}

void DataManager::Update_Items()
{

}

void DataManager::Update_Inventorys()
{
	//UI* curUI = context->GetSubsystem<UIManager>()->GetCurrentUI();
	//if (curUI)
	//{
	//	auto inventory = curUI->GetComponents<Inventory>();
	//	if (inventory.size() > 0)
	//		inventory[0]->AddInventoryBox(3, 4, static_cast<Data_Item*>(itemDatas["Wood Sword"]));
	//}
}

void DataManager::Update_Field()
{
}

void DataManager::Update_Portal()
{
}

void DataManager::Update_Spawn()
{
	
}