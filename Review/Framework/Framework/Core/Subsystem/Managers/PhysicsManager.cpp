#include "Framework.h"
#include "PhysicsManager.h"

#define CHINK 0.1f

PhysicsManager::PhysicsManager(Context* context)
	: ISubsystem(context)
	, _gravity(0.0f, -0.392f, 0.0f)
{
	timer = context->GetSubsystem<Timer>();
	input = context->GetSubsystem<Input>();
	dataManager = context->GetSubsystem<DataManager>();
	sceneManager = context->GetSubsystem<SceneManager>();
	monsterManager = context->GetSubsystem<MonsterManager>();

	EventSystem::Get()->Subscribe(EventType::Update, EVENT_HANDLER(Update));
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Clear()
{
	_movables.clear();
	_movables.shrink_to_fit();
	_unMovables.clear();
	_unMovables.shrink_to_fit();
	_effects.clear();
	_effects.shrink_to_fit();
	_characterRigidBodies.clear();
	_characterRigidBodies.shrink_to_fit();
	_characters.clear();
	_characters.shrink_to_fit();
}

const bool PhysicsManager::Initialize()
{
	_blocks.clear();
	_blocks.shrink_to_fit();
	try {
		_blocks.reserve(1024 * 1024);
		_blocks.resize(1024 * 1024);   // error 처리 필요
	}
	catch (std::bad_alloc) {
		LOG_ERROR("Out of Memory");
		return false;
	}

	return true;
}

void PhysicsManager::Update()
{
	if (!monsterManager)
		monsterManager = context->GetSubsystem<MonsterManager>();

	if (!timer->IsUpdatedFPS())
		return;

	for (auto& _character : _characters)
	{
		if(_character->GetComponent<Controller>())
			_character->GetComponent<Controller>()->SetInteraction(nullptr);

		for (auto& _effect : monsterManager->GetEffects(MonsterEffectType::Skill_Effect))   // 스킬 처리
			Update_Character_by_Effect_for_Attack(_character, _effect);
		for (auto& _effect : _effects)
			Update_Character_by_Effect(_character, _effect);
	}

	if (auto _protagonist = context->GetSubsystem<GameManager>()->GetProtagonist())  // dropped item
	{
		for (auto& _effect : monsterManager->GetEffects(MonsterEffectType::Dropped_Item))
			Update_Character_by_Effect_for_Dropped_Item(_protagonist, _effect);
	}

	for (auto& _movable : _movables)  // 선 중력처리
	{
		_movable->AddMoveVector(_gravity);
		_movable->Translate_Tmp();
		_movable->SetGroundFlag(0);
	}
	for (auto& _characterRigidBody : _characterRigidBodies)  // 선 중력처리
	{
		_characterRigidBody->AddMoveVector(_gravity);
		_characterRigidBody->Translate_Tmp();
		_characterRigidBody->SetGroundFlag(0);
	}
	for (auto& _item : monsterManager->GetEffects(MonsterEffectType::Dropped_Item))  //  선 중력처리
	{
		if (_item->IsActive())
		{
			RigidBody* _body = _item->GetComponent<RigidBody>();
			_body->AddMoveVector_Limited(_gravity);
			_body->Translate_Tmp();
			_body->SetGroundFlag(0);
		}
	}


	for (auto& _unMovable : _unMovables)    // unmovable 과 먼저 처리
	{
		for (auto& _movable : _movables)
			Update_by_UnMovable(_movable, _unMovable->GetBoundBox());

		for (auto& _characterRigidBody : _characterRigidBodies)
			Update_by_UnMovable(_characterRigidBody, _unMovable->GetBoundBox());
	}

	for (auto& _movable : _movables)    // 블럭들이랑 다음 처리
		Update_by_Blocks(_movable);
	for (auto& _characterRigidBody : _characterRigidBodies)
		Update_by_Blocks(_characterRigidBody);
	for (auto& _item : monsterManager->GetEffects(MonsterEffectType::Dropped_Item))
	{
		if (_item->IsActive())
			Update_by_Blocks(_item->GetComponent<RigidBody>());
	}
	 
	for (auto& _movable : _movables)    // 결정된거 이동
	{	 
		_movable->GetBoundBox().GetCenter();
		_movable->Translate();
	}
	for (auto& _characterRigidBody : _characterRigidBodies)
		_characterRigidBody->Translate();
	
	for (auto& _item : monsterManager->GetEffects(MonsterEffectType::Dropped_Item))
	{
		if (_item->IsActive())
			_item->GetComponent<RigidBody>()->Translate();
	}

}

void PhysicsManager::AddActor(class Actor* actor)
{
	if (!actor)
		return;
	RigidBody* rigidBody = actor->GetComponent<RigidBody>();
	
	if (!rigidBody)
		return;

	RigidBodyType type = rigidBody->GetRigidBodyType();
	
	switch (type)
	{
	case RigidBodyType::Movable: _movables.emplace_back(rigidBody); break;
	case RigidBodyType::unMovable: _unMovables.emplace_back(rigidBody); break;
	case RigidBodyType::Character: _characterRigidBodies.emplace_back(rigidBody); _characters.emplace_back(actor); break;
	case RigidBodyType::Effect: _effects.emplace_back(actor); break;
	}
}

void PhysicsManager::AcquireScene(Scene* scene)
{
	if (!scene) return;

	_movables.clear();
	_movables.shrink_to_fit();
	_movables.reserve(500);
	_unMovables.clear();
	_unMovables.shrink_to_fit();
	_unMovables.reserve(500);
	_effects.clear();
	_effects.shrink_to_fit();
	_effects.reserve(500);
	_characterRigidBodies.clear();
	_characterRigidBodies.shrink_to_fit();
	_characterRigidBodies.reserve(500);
	_characters.clear();
	_characters.shrink_to_fit();
	_characters.reserve(100);

	for (auto& actor : scene->GetActors())
		AddActor(actor);

	Vector3 offset = Vector3(BLOCK_SIZE / 2.0f, BLOCK_SIZE / 2.0f, 0);
	Vector3 center = Vector3(0, 0, 0);
	_width = scene->GetDataField()->_width;
	_height = scene->GetDataField()->_height;
	data_blocks = scene->GetDataField()->_blocks;

	for (int i = 0 ; i < data_blocks.size() ; i++)
	{
		if (static_cast<uint>(data_blocks[i]) <= 00000 ||
			static_cast<uint>(data_blocks[i]) % 1000 >= 100 || 
			static_cast<uint>(data_blocks[i]) >= 98000)  // not air, not tile
		{
			_blocks[i].Init(Vector3(999999, 999999, 999999), Vector3(999999, 999999, 999999));
			continue;
		}
		center = { (-_width / 2 + i % _height) * BLOCK_SIZE, (-_height / 2 + i / _height) * BLOCK_SIZE, 0 };
		_blocks[i].Init(center - offset , center + offset);
	}
}

void PhysicsManager::AcquireMonsters()
{
	for (auto& actor : context->GetSubsystem<MonsterManager>()->GetMonsters())
		AddActor(actor);
}

void PhysicsManager::Update_by_Blocks(RigidBody* other)
{
	Vector3 min = other->GetBoundBox().minPoint;
	Vector3 max = other->GetBoundBox().maxPoint;

	int _min_x = min.x / BLOCK_SIZE + _width / 2 - 1;
	int _min_y = min.y / BLOCK_SIZE + _height / 2 - 1;
	int _max_x = max.x / BLOCK_SIZE + _width / 2 + 2;  // if offset be 1, it can not sense just beside one as decimical point is ignored 
	int _max_y = max.y / BLOCK_SIZE + _height / 2 + 2;

	for (int _y = _min_y; _y < _max_y; _y++)
	{
		for (int _x = _min_x; _x < _max_x; _x++)
		{
			if (_y >= _height || _y < 0 || _x >= _width || _x < 0)
				continue;
			Update_by_UnMovable(other, _blocks[_y * _width + _x]);
		}
	}
}

void PhysicsManager::Update_by_UnMovable(RigidBody* other, BoundBox& unMovable)
{
	Vector3 _moveVector_other = other->GetMoveVector();
	BoundBox _boundBox_other = other->GetBoundBox();
	BoundBox _boundBox_unMovable = unMovable;

	Intersection check = _boundBox_other.IsInside(_boundBox_unMovable);

	switch (check)
	{
	case Intersection::Inside:
	{
		other->SetMoveVector(Vector3(3.0f, 3.0f, 0.0f));
		other->Translate_Tmp();
		other->SetMoveVector(Vector3(0, 0, 0));
		break;
	}
	case Intersection::Intersect:
	{
		Vector3 _moveVector = Vector3(0, 0, 0);
		if ((other->GetBottom() > _boundBox_unMovable.GetTop() || other->GetTop() < _boundBox_unMovable.GetBottom()))
		{
			if (_boundBox_other.minPoint.y < _boundBox_unMovable.maxPoint.y + CHINK &&
				_boundBox_unMovable.maxPoint.y + CHINK < _boundBox_other.maxPoint.y)
			{
				_moveVector += Vector3(0, _boundBox_unMovable.maxPoint.y - _boundBox_other.minPoint.y + CHINK, 0);
				other->OnGroundFlag(GroundFlag::GroundFlag_Bottom);
			}
			else if (_boundBox_other.maxPoint.y > _boundBox_unMovable.minPoint.y - CHINK &&
				_boundBox_unMovable.minPoint.y - CHINK > _boundBox_other.minPoint.y)
			{
				_moveVector += Vector3(0, _boundBox_unMovable.minPoint.y - _boundBox_other.maxPoint.y - CHINK, 0);
				other->OnGroundFlag(GroundFlag::GroundFlag_Top);
			}
		}
		else
		{
			if (_boundBox_other.minPoint.x < _boundBox_unMovable.maxPoint.x + CHINK &&
				_boundBox_unMovable.maxPoint.x + CHINK < _boundBox_other.maxPoint.x)
			{
				_moveVector += Vector3(_boundBox_unMovable.maxPoint.x - _boundBox_other.minPoint.x + CHINK, 0, 0);
				other->OnGroundFlag(GroundFlag::GroundFlag_Left);
			}
			else if (_boundBox_other.maxPoint.x > _boundBox_unMovable.minPoint.x - CHINK &&
				_boundBox_unMovable.minPoint.x - CHINK > _boundBox_other.minPoint.x)
			{
				_moveVector += Vector3(_boundBox_unMovable.minPoint.x - _boundBox_other.maxPoint.x - CHINK, 0, 0);
				other->OnGroundFlag(GroundFlag::GroundFlag_Right);
			}
		}
		
		other->SetMoveVector(_moveVector);
		other->Translate_Tmp();
		other->SetMoveVector(Vector3(0, 0, 0));

		break;
	}
	}
}

void PhysicsManager::Update_Movable_by_Character(RigidBody* other, RigidBody* unMovable)
{
}

void PhysicsManager::Update_Movable_by_Movable(RigidBody* other, RigidBody* unMovable)
{
}

void PhysicsManager::Update_Character_by_Movable(RigidBody* other, RigidBody* unMovable)
{
}

void PhysicsManager::Update_Character_by_Effect_for_Attack(Actor* other, Actor* effect)
{
	if (!effect->IsActive() || !other->IsActive())
		return;

	Controller* controller = other->GetComponent<Controller>();
	Controller* controller_effect = effect->GetComponent<Controller>();

	if (controller->IsInvincible() || controller_effect->GetTeam() == controller->GetTeam())
		return;

	RigidBody* _rigidBody = other->GetComponent<RigidBody>();
	if (!_rigidBody)
		return;

	RigidBody* _rigidBody_effect = effect->GetComponent<RigidBody>();
	if (!_rigidBody_effect || _rigidBody_effect->GetBoundBox().GetSize().x < 0)
		return;

	Intersection check = _rigidBody->GetBoundBox().IsInside(_rigidBody_effect->GetBoundBox());

	if (check != Intersection::Outside)
	{
		Data_Skill* effect_data = controller_effect->GetAttack1Data();
		if (effect_data == nullptr)
			return;

		Vector3 _moveVector = effect_data->_knockBack;
		if (controller_effect->GetDirect() == 0)
			_moveVector.x *= -1;

		if (controller_effect->GetActType() == 5 && controller->GetActType() == 4)  // garud attack1
		{
			auto controller_effect_parent = controller_effect->GetParentActor()->GetComponent<Controller>();
			controller_effect_parent->Hit(effect_data, controller, Vector3(-_moveVector.x, _moveVector.y, 0), 3.0f);
			controller_effect->SetTeam(controller_effect->GetTeam() == 1 ? 0 : 1);
			controller_effect->MakeReverce();
		}
		else if (controller_effect->GetActType() == 4)
		{
			return;
		}
		else
		{
			controller->SetHitRange(effect_data->_distance + effect_data->_size_stand * 0.5f);
			controller->Hit(effect_data, controller_effect->GetParentActor()->GetComponent<Controller>(), _moveVector);
			monsterManager->Load_Skill_Effect(*other, effect_data, other->GetComponent<Animator>()->IsReversed(), AnimationMotionType::Hit);
		}
	}

}

void PhysicsManager::Update_Character_by_Effect_for_Dropped_Item(Actor* other, Actor* effect)
{
	if (!input->KeyPress(KeyCode::KEY_V)) return;
	if (!effect->IsActive() || !other->IsActive()) return;

	Controller* controller = other->GetComponent<Controller>();
	Controller* controller_effect = effect->GetComponent<Controller>();

	if (!controller || !controller_effect) return;

	RigidBody* _rigidBody = other->GetComponent<RigidBody>();
	if (!_rigidBody) return;

	RigidBody* _rigidBody_effect = effect->GetComponent<RigidBody>();
	if (!_rigidBody_effect) return;

	Intersection check = _rigidBody->GetBoundBox().IsInside(_rigidBody_effect->GetBoundBox());

	if (check != Intersection::Outside)
	{
		Data_Item* item_Data = controller_effect->GetItemData();
		if (item_Data == nullptr)
			return;

		context->GetSubsystem<InventoryManager>()->InsertItemAuto(item_Data->GetName(), 1);
		effect->SetActive(false);
	}
}

void PhysicsManager::Update_Character_by_Effect(Actor* other, Actor* effect)
{
	if (!effect->IsActive() || !other->IsActive())
		return;

	Controller* controller = other->GetComponent<Controller>();
	Controller* controller_effect = effect->GetComponent<Controller>();

	if (!controller || !controller_effect) return;
	if (other->GetComponent<Controller>()->IsInvincible()) return;

	RigidBody* _rigidBody = other->GetComponent<RigidBody>();
	if (!_rigidBody)
		return;

	RigidBody* _rigidBody_effect = effect->GetComponent<RigidBody>();
	if (!_rigidBody_effect)
		return;

	Intersection check = _rigidBody->GetBoundBox().IsInside(_rigidBody_effect->GetBoundBox());

	if (check != Intersection::Outside)
		other->GetComponent<Controller>()->SetInteraction(effect);
}

ScannedResult PhysicsManager::ScanField(const Vector3& pos, const Vector3& scale, const int& direct)
{
	if (this->data_blocks.size() < 1)
		return ScannedResult::Flat;

	auto _loc = DataManager::BlockPosToBlockLoc(_width, _height, pos - Vector3(0, scale.y / 2 - 25.0f, 0));
	int _loc_x = _loc.first;
	int _loc_y = _loc.second;
	int _range = 3;

	int _scane_x = direct == 0 ?
		_loc_x - (scale.x / 2) / BLOCK_SIZE - ((int)(scale.x / 2)% (int)BLOCK_SIZE > 0 ? 1 : 0) :
		_loc_x + (scale.x / 2) / BLOCK_SIZE + ((int)(scale.x / 2)% (int)BLOCK_SIZE > 0 ? 1 : 0) + 1 ; // direct 0 is left, 1 is right
	int _checked_lower = 0;
	int _checked_upper = 0;

	if (data_blocks.size() < _loc_y * _width + _loc_x)  // exception
		return ScannedResult::Flat;

	for (int _y = _loc_y ; _y < _loc_y + _range; _y++)   // check Wall
	{
		if (static_cast<uint>(data_blocks[_y * _width + _scane_x]) <= 00000 || static_cast<uint>(data_blocks[_y * _width + _scane_x]) % 1000 >= 100)
			continue;
		_checked_upper += 1;
	}
	if (_checked_upper == _range)
		return ScannedResult::Wall;
	else if (_checked_upper > 0)
		return ScannedResult::Stair_Upper;

	for (int _y = _loc_y - _range; _y < _loc_y; _y++)   // check Cliff
	{
		if (static_cast<uint>(data_blocks[_y * _width + _scane_x]) <= 00000 || static_cast<uint>(data_blocks[_y * _width + _scane_x]) % 1000 >= 100)
			continue;	
		_checked_lower += 1;
	}
	if (_checked_lower == 0)
		return ScannedResult::Cliff;
	else if (_checked_lower != _range)
		return ScannedResult::Stair_Lower;

	return ScannedResult::Flat;
}
