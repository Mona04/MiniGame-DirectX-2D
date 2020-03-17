#pragma once
#include "pch.h"

#define BLOCK_SIZE 30.0f

enum class BlockKind : uint
{
	Air = 10000,
	Glass_Up = 11001,
};

class Data_Field : public IData
{
private:
	friend class DataManager;

public:
	static std::vector<BlockKind> blockKinds;

private:
	Data_Field(const std::string& name);
	~Data_Field() = default;

	void SaveToFile(const std::string& path) {};
	void LoadFromFile(const std::string& path) {};

	void Clear();

	void Init_Default(const int& width, const int& height);
	void Init_Plain(const int& width, const int& height);

public:
	std::vector<BlockKind> _blocks_back;
	std::vector<BlockKind> _blocks;
	std::vector<BlockKind> _blocks_functional;
	std::vector<BlockKind> _blocks_front;

	int _width;
	int _height;
};