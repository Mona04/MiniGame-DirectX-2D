#pragma once
#include "pch.h"
#include "IData.h"

class Data_Skill : public IData
{
private:
	friend class DataManager;

public:
	Data_Skill(const std::string& name)
	{
		SetType(DataType::Skill);
		SetName(name);
	}
	~Data_Skill() = default;

	void SaveToFile(const std::string& path);
	void LoadFromFile(const std::string& path);

public:
	std::string _skillName = "luckySeven";

	D3DXVECTOR3 _size_stand = D3DXVECTOR3(10, 10, 0);
	D3DXVECTOR3 _size_hit = D3DXVECTOR3(10, 10, 0);
	D3DXVECTOR3 _distance = D3DXVECTOR3(0, 0, 0);
	float _delay_actor; // delay for actor
	float _delay_stand; // delay for attack effect 
	float _delay_hit;  // delay for attacked effect
	float _damage_fire = 1;
	float _damage_water = 1;
	float _damage_light = 1;
	float _damage_dark = 1;
	float _hp_consumed = 0;
	float _mp_consumed = 0;
	float _sp_consumed = 0;

	D3DXVECTOR3 _knockBack = D3DXVECTOR3(10.0f, 7.0f, 0.0f);
};