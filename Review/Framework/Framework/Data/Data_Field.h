#pragma once
#include "Framework.h"

#define BLOCK_SIZE 30.0f

typedef unsigned int BlockKind;    // 1000 * region_num + 000, 001 ~ block , + 100, 101 ~ back 
									// 99000  ~ npc, 98000 ~ special

class Data_Field : public IData
{
private:
	friend class DataManager;
	friend class GameManager;

private:
	Data_Field(const std::string& name);
	~Data_Field() = default;

	void SaveToFile(const std::string& path);
	void LoadFromFile(const std::string& path);

	void Clear();

public:
	void SetBackGroundPath(const std::string& path) { _backGroundPath = path; }
	const std::string& GetBackGroundPath() { return  _backGroundPath; }

public:
	void Init_Region(const int& nFloor);
	static int GetBlockType(const BlockKind& kind) { if (kind == 0) return -1; return (kind % 1000) / 100; }
	static int GetBlockRegion(const BlockKind& kind) { return kind / 1000; }

public:
	std::vector<BlockKind> _blocks_back;
	std::vector<BlockKind> _blocks;
	std::vector<BlockKind> _blocks_functional;
	std::vector<BlockKind> _blocks_front;
	std::string _backGroundPath = "Map/Back/Grassy.png";
	std::string _bgmPath = "Bgm/Main.mp3";

	int _width;
	int _height;
	int _region = 1;
};