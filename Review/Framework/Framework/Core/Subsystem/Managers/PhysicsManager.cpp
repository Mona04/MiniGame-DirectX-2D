#include "Framework.h"
#include "PhysicsManager.h"


#define CHINK 0.2f

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
	_movables.clear();             _movables.shrink_to_fit();
	_unMovables.clear();           _unMovables.shrink_to_fit();
	_overlappeds.clear();          _overlappeds.shrink_to_fit();
	_characters.clear();           _characters.shrink_to_fit();
	data_blocks.clear();           data_blocks.shrink_to_fit();
	_blocks.clear();               
}

const bool PhysicsManager::Initialize()
{
	_blocks.clear();
	_blocks.shrink_to_fit();
	try {
		_blocks.reserve(1024 * 1024);
		_blocks.resize(1024 * 1024);   // error 贸府 鞘夸
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

	const auto& effects = monsterManager->GetEffects(MonsterEffectType::Skill_Effect);
	for (RigidBody* rb : _characters)
	{
		for (Actor* _effect : effects)   // 胶懦 老褒 贸府
			Update_Character_by_Effect_for_Attack(rb->GetOwner(), _effect);
	}

	Update_Process();
}

void PhysicsManager::AddActor(class Actor* actor)
{
	if (!actor) return;

	RigidBody* rigidBody = actor->GetComponent<RigidBody>();
	if (!rigidBody) return;

	RigidBodyType type = rigidBody->GetRigidBodyType();
	
	switch (type)
	{
	case RigidBodyType::Movable:   _movables.emplace_back(rigidBody); break;
	case RigidBodyType::unMovable: _unMovables.emplace_back(rigidBody); break;
	case RigidBodyType::Character: _characters.emplace_back(rigidBody); break;
	case RigidBodyType::Overlap:    _overlappeds.emplace_back(rigidBody); break;
	}
}

void PhysicsManager::AcquireScene(Scene* scene)
{
	if (!scene) return;

	Clear();

	_movables.reserve(500);
	_unMovables.reserve(500);
	_overlappeds.reserve(500);
	_characters.reserve(100);

	for (auto& actor : scene->GetActors())
		AddActor(actor);

	Vector3 offset = Vector3(BLOCK_SIZE / 2.0f, BLOCK_SIZE / 2.0f, 0);
	Vector3 center = Vector3(0, 0, 0);
	if (Data_Field* field_data = scene->GetDataField())
	{
		_width = field_data->_width;
		_height = field_data->_height;
		data_blocks = field_data->_blocks;
	}
	else {
		_width = 10; _height = 10; 
		data_blocks.clear(); data_blocks.shrink_to_fit();
	}

	for (int i = 0 ; i < data_blocks.size() ; i++)
	{
		if (static_cast<uint>(data_blocks[i]) <= 00000 ||
			static_cast<uint>(data_blocks[i]) % 1000 >= 100 || 
			static_cast<uint>(data_blocks[i]) >= 98000)  // not air, not tile
		{
			_blocks[i].Init(Vector3(100, 999999, 999999), Vector3(999999, 999999, 999999));
			continue;
		}
		center = { (-_width / 2 + i % _height) * BLOCK_SIZE, (-_height / 2 + i / _height) * BLOCK_SIZE, 0 };
		_blocks[i].Init(center - offset , center + offset);
	}
}

void PhysicsManager::ChangeRigidBodyType(RigidBody* rb, int type)
{
	if (!rb) return;	
	RigidBodyType old = rb->GetRigidBodyType();
	RigidBodyType to = RigidBodyType(type);
	std::vector<RigidBody*>* buf = nullptr;

	switch (old)
	{
	case RigidBodyType::unMovable: buf = &_unMovables; break;
	case RigidBodyType::Movable:   buf = &_movables; break;
	case RigidBodyType::Character: buf = &_characters; break;
	case RigidBodyType::Overlap:   buf = &_overlappeds; break;
	}
	if (!buf) return;
	auto find = std::find(buf->begin(), buf->end(), rb);
	if(find != buf->end())
		buf->erase(find);

	switch (to)
	{
	case RigidBodyType::unMovable: buf = &_unMovables; break;
	case RigidBodyType::Movable:   buf = &_movables; break;
	case RigidBodyType::Character: buf = &_characters; break;
	case RigidBodyType::Overlap:   buf = &_overlappeds; break;
	}
	buf->push_back(rb);
}

// === UPdate ==============================================================================

void PhysicsManager::Update_Process()
{
	// === Gravity ==================================================
	for (auto& rb : _movables)      Update_Gravity(rb);	
	for (auto& rb : _characters)	Update_Gravity(rb);
	for (auto& _item : monsterManager->GetEffects(MonsterEffectType::Dropped_Item))
		if (_item->IsActive())
			Update_Gravity(_item->GetComponent<RigidBody>());

	for (int bUpdown = 0; bUpdown <= 1; bUpdown++)
	{
		// === Upate by Unmovable ====================================
		for (auto& rb : _movables)
			for (auto& _unMovable : _unMovables)
				Update_by_UnMovable(rb, _unMovable->GetBoundBox(), bUpdown);
		for (auto& rb : _characters)
			for (auto& _unMovable : _unMovables)
				Update_by_UnMovable(rb, _unMovable->GetBoundBox(), bUpdown);
		// === Update by Blocks ======================================
		for (auto& rb : _movables)      Update_by_Blocks(rb, bUpdown);
		for (auto& rb : _characters)	Update_by_Blocks(rb, bUpdown);
		for (auto& _item : monsterManager->GetEffects(MonsterEffectType::Dropped_Item))
			if (_item->IsActive())
				Update_by_Blocks(_item->GetComponent<RigidBody>(), bUpdown);
	}

	// === Fix the movement ======================================
	for (auto& rb : _movables)              rb->Translate();
	for (auto& rb : _characters)			rb->Translate();
	for (auto& _item : monsterManager->GetEffects(MonsterEffectType::Dropped_Item))
	{
		if (_item->IsActive())
			_item->GetComponent<RigidBody>()->Translate();
	}
}

void PhysicsManager::Update_Gravity(RigidBody* other)
{
	const Vector3 gravity = _gravity * _delta * 2.f;
	other->AddVelocity(gravity);
	other->Translate_Tmp(other->_moveVector + other->_velocity);
	other->SetMoveVector(0);
	other->SetGroundFlag(0);
}

void PhysicsManager::Update_by_Blocks(RigidBody* other, bool bUpdown)
{
	if (!other) return;
	Vector3 min = other->GetBoundBox().minPoint;
	Vector3 max = other->GetBoundBox().maxPoint;


	int min_x = min.x / BLOCK_SIZE + _width / 2 - 1;
	int min_y = min.y / BLOCK_SIZE + _height / 2 - 1;
	int max_x = max.x / BLOCK_SIZE + _width / 2 + 2;  // if offset be 1, it can not sense just beside one as decimical point is ignored 
	int max_y = max.y / BLOCK_SIZE + _height / 2 + 2;

	for (int y = max_y - 1; y >= min_y; y--)  // From Bottom Calc
		for (int x = min_x; x < max_x; x++)
		{
			if (y >= _height || y < 0 || x >= _width || x < 0) continue;
			Update_by_UnMovable(other, _blocks[y * _width + x], bUpdown);
		}
}

void PhysicsManager::Update_by_UnMovable(RigidBody* other, BoundBox& unMovable, bool bUpdown)
{
	BoundBox _boundBox_other = other->GetBoundBox();
	BoundBox _boundBox_unMovable = unMovable;

	Intersection check = _boundBox_other.IsInside(_boundBox_unMovable);

	switch (check)
	{
	case Intersection::Inside:
	{
		other->Translate_Tmp(Vector3(3.0f, 3.0f, 0.0f));
		other->SetVelocity(0);
		other->SetMoveVector(Vector3(0, 0, 0));
		break;
	}
	case Intersection::Intersect:
	{
		Vector3 _moveVector = Vector3(0, 0, 0);
		if ((other->GetBottom() > _boundBox_unMovable.GetTop() || other->GetTop() < _boundBox_unMovable.GetBottom()))
		{
			if (!bUpdown) return;

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
			other->_velocity.y = 0;
		}
		else
		{
			if (bUpdown) return;

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
		
		other->Translate_Tmp(_moveVector);
		other->_velocity.x = 0;

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
	if (!controller || !controller_effect) return;

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

// === Helpers =================================================================================

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

std::vector<class Actor*> PhysicsManager::TraceByVectors(Actor* other, std::vector<class Actor*> in)
{
	std::vector<Actor*> res;
	if (!monsterManager || !other) return res;

	Controller* controller = other->GetComponent<Controller>();
	if (!controller) return res;

	RigidBody* rigidBody = other->GetComponent<RigidBody>();
	if (!rigidBody) return res;

	for (Actor* item : in)
	{
		if (!item || !item->IsActive()) continue;

		RigidBody* item_rigidBody = item->GetComponent<RigidBody>();
		if (!item_rigidBody) continue;

		Intersection check = rigidBody->GetBoundBox().IsInside(item_rigidBody->GetBoundBox());
		if (check != Intersection::Outside)
			res.push_back(item);
	}

	return res;
}

std::vector<class Actor*> PhysicsManager::TraceByVectors(Actor* other, std::vector<class RigidBody*> in)
{
	std::vector<Actor*> res;
	if (!monsterManager || !other) return res;

	Controller* controller = other->GetComponent<Controller>();
	if (!controller) return res;

	RigidBody* rigidBody = other->GetComponent<RigidBody>();
	if (!rigidBody) return res;

	for (RigidBody* item : in)
	{
		if (!item) continue;

		Actor* owner = item->GetOwner();
		if (!!owner && !owner->IsActive()) continue;

		Intersection check = rigidBody->GetBoundBox().IsInside(item->GetBoundBox());
		if (check != Intersection::Outside)
			res.push_back(owner);
	}

	return res;
}