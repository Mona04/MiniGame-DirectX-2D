#pragma once

enum class ComponentType : uint
{
	Unknown,
	Transform,
	Renderable,
	Animator,
	RigidBody,
	AudioResource,
	Scripter,
	Controller,
	//	Light,
	//	Particle
};

enum class RigidBodyType : uint
{
	unMovable,  // ��������
	Movable,  // ������ ����
	Character,  // ĳ����
	Effect,
};

class Actor
{
public:
	static void SaveToFile(const std::string& monsterName, const int& lv, const int& type);
	static void SaveToMobData(const std::string& monsterName, const int& lv);
	static void SaveToMobSkill(const int& lv);
	static void SaveToDialogData(const int& nFloor);
};