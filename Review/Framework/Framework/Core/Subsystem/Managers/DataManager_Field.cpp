#include "Framework.h"
#include "DataManager.h"

void DataManager::Init_Default(const std::string& name, const int& width, const int& height)
{
	Data_Field* _field = GetData<Data_Field>(name);
	if (!_field)
	{
		LOG_ERROR_F("%s does not exist", name.c_str());
		return;
	}
	_field->Clear();

	_field->_width = width % 2 == 0 ? width : width + 1;
	_field->_height = height % 2 == 0 ? height : height + 1;

	_field->_blocks.reserve(width * height);
	_field->_blocks_back.reserve(width * height);
	_field->_blocks_front.reserve(width * height);
	_field->_blocks_functional.reserve(width * height);

	BlockKind tile_default = _field->_region * 1000 + 0;

	for (int j = -height / 2; j < height / 2; j++)
	{
		for (int i = -width / 2; i < width / 2; i++)
		{
			_field->_blocks.emplace_back(0);
			_field->_blocks_back.emplace_back(0);
			_field->_blocks_front.emplace_back(0);
			_field->_blocks_functional.emplace_back(0);
		}
	}
	for (int i = 0; i < width; i++)
	{
		_field->_blocks[0 * width + i] = tile_default;
		_field->_blocks[(height - 1) * width + i] = tile_default;
	}
	for (int j = 0; j < height; j++)
	{
		_field->_blocks[j * width + 0] = tile_default;
		_field->_blocks[j * width + width - 1] = tile_default;
	}
}

void DataManager::Init_Plain(const std::string& name, const int& width, const int& height, const int& min, const int& max)
{
	Data_Field* _field = GetData<Data_Field>(name);
	Data_Spawn* _spawn = GetData<Data_Spawn>(name);

	if (!_field)
	{
		LOG_ERROR_F("%s does not exist", name.c_str());
		return;
	}

	int num_InflectionPoint = Math::Random(0, height / 10);
	std::vector<int> height_InflectionPoint;
	std::vector<int> xPoint_InflectionPoint;

	height_InflectionPoint.emplace_back(Math::Random(min, max));  // 둘은 크기가 다름
	xPoint_InflectionPoint.emplace_back(width - 2);
	height_InflectionPoint.emplace_back(Math::Random(min, max));

	for (int i = 0; i < num_InflectionPoint; i++)
	{
		height_InflectionPoint.emplace_back(Math::Random(min, max));
		xPoint_InflectionPoint.emplace_back(Math::Random(1, width - 2));
	}
	std::sort(xPoint_InflectionPoint.begin(), xPoint_InflectionPoint.end());

	BlockKind tile_default = _field->_region * 1000 + 0;
	BlockKind tile_default_up = _field->_region * 1000 + 1;

	int _cur = 0; int _before = 0;  int _index = 0;
	for (auto& _next : xPoint_InflectionPoint)
	{
		while (_cur <= _next)
		{
			int height_tmp = height_InflectionPoint[_index] + ((height_InflectionPoint[_index + 1] - height_InflectionPoint[_index]) * (_cur - _before)) / (_next - _before);

			for (int i = 0; i < height_tmp - 1; i++)
				_field->_blocks[i * width + _cur] = tile_default;
			_field->_blocks[(height_tmp - 1) * width + _cur] = tile_default_up;
			
			if (height_tmp < height && Math::Gambling(0.4f))
				_field->_blocks_back[height_tmp * width + _cur] =  GetRandomBlockKind(_field->_region, 1);
			if (_spawn && Math::Gambling(0.1f))
				_spawn->_spawnInfoList.emplace_back(SpawnInfo(BlockLocToBlockPos(width, height, _cur, height_tmp + 3), false));
			
			_cur++;
		}
		_index++;
		_before = _next;
	}
}

void DataManager::Init_SkyStairWay(const std::string& name, const int& width, const int& height, const int& min_height, const int& max_height, const int& suc)
{
	// min is min height, max is max height
	Data_Field* _field = GetData<Data_Field>(name);
	if (!_field)
	{
		LOG_ERROR_F("%s does not exist", name.c_str());
		return;
	}

	int _island_width = 4;
	int _offset_x = 8;
	int _offset_y = 8;
	int _successive_stack = 0;
	int _direct = 0;
	int _point_x = Math::Random(0, width);
	int _point_y = max_height - _offset_y + 3;
	bool bReverse = true;

	while( _point_y < height)
	{		
		if (_island_width < 4)
			break;

		_point_y += _offset_y;
		_point_x += _direct == 0 ? -_island_width - _offset_x : _island_width + _offset_x;
		if (_point_x - _island_width / 2.0f < 0 || _point_x + _island_width / 2.0f >= width)
		{
			_direct = _direct == 0 ? 1 : 0;
			_point_x += _direct == 0 ? 2.0f * (-_island_width - _offset_x) : 2.0f * (_island_width + _offset_x);
		}

		Make_SkyIsland(name, width, height, _point_x, _point_y, _island_width);

		_successive_stack++;
		if (_successive_stack >= suc)
		{
			_successive_stack = 0;
			_direct = _direct == 0 ? 1 : 0;
		}

		if (bReverse)
		{
			if (_island_width < 10)
				_island_width += 2;
			else 
				bReverse = false;
		}
		else 
			_island_width -= 1;
	}
}

void DataManager::Make_SkyIsland(const std::string& name, const int& width, const int& height, const int& point_x, const int& point_y, const int& island_width)
{
	Data_Field* _field = GetData<Data_Field>(name);
	Data_Spawn* _spawn = GetData<Data_Spawn>(name);
	if (!_field)
	{
		LOG_ERROR_F("%s does not exist", name.c_str());
		return;
	}

	BlockKind tile_default = _field->_region * 1000 + 0;
	BlockKind tile_default_up = _field->_region * 1000 + 1;

	int cur_height = 0; int cur_width = 0;

	for (cur_width = point_x - island_width / 2.0f; cur_width <= point_x + island_width / 2.0f; cur_width++)
	{
		int height_offset = Math::Min(cur_width - (point_x - island_width), (point_x + island_width) - cur_width) / 2.0f;
		for (cur_height = point_y - height_offset; cur_height < point_y - 1; cur_height++)
		{
			_field->_blocks[cur_height * width + cur_width] = tile_default;
		}
	}
	
	cur_height = point_y - 1;
	for (cur_width = point_x - island_width / 2.0f; cur_width <= point_x + island_width / 2.0f; cur_width++)
	{
		_field->_blocks[cur_height * width + cur_width] = tile_default_up;
		if (Math::Gambling(0.2f))
			_field->_blocks_back[(cur_height + 1) * width + cur_width] = GetRandomBlockKind(_field->_region, 1);
		if (Math::Gambling(0.3f))
			_spawn->_spawnInfoList.emplace_back(SpawnInfo(BlockLocToBlockPos(width, height, cur_width, cur_height + 3), true));
	}
}

void DataManager::Init_Ect(const std::string& name, const int& width, const int& height)
{
	Data_Field* _field = GetData<Data_Field>(name);
	Data_Spawn* _spawn = GetData<Data_Spawn>(name);
	if (!_field)
	{
		LOG_ERROR_F("%s does not exist", name.c_str());
		return;
	}

	BlockKind portal = 98 * 1000 + 0;
	BlockKind morian = 99 * 1000 + 0;
	BlockKind cichol = 99 * 1000 + 1;
	BlockKind blony = 99 * 1000 + 2;
	BlockKind fleta = 99 * 1000 + 3;

	for (int y = height - 3; y > -1 ; y--)
	{
		for (int x = 3; x < width - 3; x++)
		{
			if (Data_Field::GetBlockType(_field->_blocks[y * width + x]) == 0 && Data_Field::GetBlockType(_field->_blocks[(y + 1) * width + x]) == -1 )
			{
				int end_x = x;
				while (Data_Field::GetBlockType(_field->_blocks[y * width + end_x]) == 0)
					end_x++;
				_field->_blocks[(y + 1) * width + (x + end_x) / 2] = portal;
				y = -1; break;
			}
		}
	}

	std::vector<std::pair<int, int>> locs; 
	while (locs.size() < 4)
	{
		bool isRedup = false;
		int new_x = rand() % (width - 3) + 3;
		int new_y = 2;

		if (locs.size() == 0)
			new_x % 50;

		for (const auto& loc : locs)
		{
			if (loc.first == new_x)
			{
				isRedup = true;
				break;
			}
		}

		if(!isRedup)
		{
			while (Data_Field::GetBlockType(_field->_blocks[new_y * width + new_x]) != -1)
				new_y++;

			if (IsConcave(name, width, height, new_x, new_y))
			{
				switch (locs.size())
				{
				case 0: _field->_blocks[new_y * width + new_x] = morian; break;
				case 1: _field->_blocks[new_y * width + new_x] = cichol; break;
				case 2: _field->_blocks[new_y * width + new_x] = blony; break;
				case 3: _field->_blocks[new_y * width + new_x] = fleta; break;
				}
				locs.emplace_back(std::pair(new_x, new_y));
			}
		}
	}
}

const bool DataManager::IsConcave(const std::string& name, const int& width, const int& height, const int& point_x, const int& point_y)
{
	Data_Field* _field = GetData<Data_Field>(name);
	if (!_field)
	{
		LOG_ERROR_F("%s does not exist", name.c_str());
		return false;
	}

	if (Data_Field::GetBlockType(_field->_blocks[ (point_y - 1) * width + point_x]) == 0 &&
		Data_Field::GetBlockType(_field->_blocks[(point_y ) * width + point_x]) == -1 &&
		Data_Field::GetBlockType(_field->_blocks[(point_y ) * width + point_x - 1]) == -1 &&
		Data_Field::GetBlockType(_field->_blocks[(point_y) * width + point_x + 1]) == -1)
		return true;
	else return false;
}

Vector3 DataManager::BlockLocToBlockPos(const int& width, const int& height, const int& x, const int& y)
{
	//auto a = Vector3(-width / 2.0f + x, -height / 2.0f + y, 0.0f) * BLOCK_SIZE;
	return Vector3(-width / 2.0f + x, -height / 2.0f + y, 0.0f) * BLOCK_SIZE;
}

std::pair<int, int> DataManager::BlockPosToBlockLoc(const int& width, const int& height, const Vector3& pos)
{
	return std::pair<int, int>(Math::RoundDown(pos.x / BLOCK_SIZE) + width / 2, Math::RoundDown(pos.y / BLOCK_SIZE) + height / 2);
}
