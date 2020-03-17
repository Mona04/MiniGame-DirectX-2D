#include "pch.h"
#include "Data_Field.h"

std::vector<BlockKind> Data_Field::blockKinds = { BlockKind::Air, BlockKind::Glass_Up };

Data_Field::Data_Field(const std::string& name)
{
	SetType(DataType::Field);
	SetName(name);
}

void Data_Field::Clear()
{
	_width = 0; _height = 0;
	_blocks.clear(); _blocks.shrink_to_fit();
	_blocks_back.clear();  _blocks_back.shrink_to_fit();
	_blocks_functional.clear(); _blocks_functional.shrink_to_fit();
	_blocks_front.clear(); _blocks_front.shrink_to_fit();
}

void Data_Field::Init_Default(const int& width, const int& height)
{
	Clear();

	this->_width = width % 2 == 0 ? width : width + 1;
	this->_height = height % 2 == 0 ? height : height + 1;

	_blocks.reserve(width * height);
	_blocks_back.reserve(width * height);
	_blocks_front.reserve(width * height);
	_blocks_functional.reserve(width * height);

	for (int j = -height / 2; j < height / 2; j++)
	{
		for (int i = -width / 2; i < width / 2; i++)
		{
			_blocks.emplace_back(BlockKind::Air);
			_blocks_back.emplace_back(BlockKind::Air);
			_blocks_front.emplace_back(BlockKind::Air);
			_blocks_functional.emplace_back(BlockKind::Air);
		}
	}

	for (int i = -width / 2; i < width / 2; i++)
	{
		_blocks[0 * width + i + width / 2] = BlockKind::Glass_Up;
	}
}

void Data_Field::Init_Plain(const int& width, const int& height)
{
	Clear();

	this->_width = width % 2 == 0 ? width : width + 1;
	this->_height = height % 2 == 0 ? height : height + 1;

	_blocks.reserve(width * height);
	_blocks_back.reserve(width * height);
	_blocks_front.reserve(width * height);
	_blocks_functional.reserve(width * height);

	for (int j = -height / 2; j < height / 2; j++)
	{
		for (int i = -width / 2; i < width / 2; i++)
		{
			_blocks.emplace_back(BlockKind::Air);
			_blocks_back.emplace_back(BlockKind::Air);
			_blocks_front.emplace_back(BlockKind::Air);
			_blocks_functional.emplace_back(BlockKind::Air);
		}
	}
}
