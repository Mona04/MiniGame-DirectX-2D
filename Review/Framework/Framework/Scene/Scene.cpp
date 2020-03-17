#include "Framework.h"
#include "Scene.h"
#include "Camera.h"

std::string Scene::defaultDir = "../../_Assets/Scene/";

Scene::Scene(Context * context)
	: context(context)
	, data_field(nullptr)
	, data_spawn(nullptr)
{
	camera = new Camera(context);
	dataManager = context->GetSubsystem<DataManager>();
	physicsManager = context->GetSubsystem<PhysicsManager>();

	backGround = new Actor(context);
	backGround->LoadFromFile("../../_Assets/Scene/Map/backGround.actor");
	auto resolution = context->GetSubsystem<Renderer>()->GetResolution();
	backGround->GetComponent<Transform>()->SetScale(Vector3(resolution.x, resolution.y, 0) * 1.5f);
}

Scene::~Scene()
{
	SAFE_DELETE(camera);
	SAFE_DELETE(backGround);

	for (auto actor : actors)
		SAFE_DELETE(actor);

	for (auto data : field_geometry)
		SAFE_DELETE(data.second);

	for (auto buffer : field_instanceBuffer)
		SAFE_DELETE(buffer.second);

	actors.clear();
	actors.shrink_to_fit();
}

void Scene::LoadFromFile(const std::string& path)
{
	FileStream stream;
	std::string actorsFolder = defaultDir + "Scene " + FileSystem::GetIntactFileNameFromPath(path) + "/";
	std::string actorName, fieldDataName, spawnDataName;
	bool isActive, isAttacthedCamera = true;
	SetName(FileSystem::GetIntactFileNameFromPath(path));

	stream.Open(defaultDir + path, StreamMode::Read);
	{
		uint nActor = stream.ReadUInt();

		for (uint i = 0; i < nActor; i++)
		{
			stream.Read(actorName);
			stream.Read(isActive);
			stream.Read(isAttacthedCamera);

			Actor* actor = CreateActor(actorsFolder + actorName + ".actor");
			actor->SetName(actorName);
			actor->SetActive(isActive);
			actor->SetIsCameraAttached(isAttacthedCamera);

			if (isAttacthedCamera)
				camera->SetTransform(actor->GetComponent<Transform>());
		}

		stream.Read(fieldDataName);
		stream.Read(spawnDataName);

		data_field = dataManager->GetData<Data_Field>(fieldDataName);
		data_spawn = dataManager->GetData<Data_Spawn>(spawnDataName);

		if (data_field)
		{
			Init_Field_InstanceBuffer();
			camera->SetFieldData(data_field);
			backGround->GetComponent<Renderable>()->SetTexture(TextureType::Albedo, data_field->GetBackGroundPath(), data_field->GetBackGroundPath());
			//backGround->AddComponent<AudioClip>()->SetLoop(true);
			//backGround->GetComponent<AudioClip>()->
		}
	}
	stream.Close();	 
}

void Scene::SaveToFile(const std::string& path)
{
	FileStream stream;
	std::string actorsFolder = defaultDir + "Scene " + FileSystem::GetIntactFileNameFromPath(path) + "/";
	FileSystem::MakeDirectory(actorsFolder);
	std::string actorName;

	stream.Open(defaultDir + path, StreamMode::Write);
	{
		stream.Write(actors.size());

		for (const auto& actor : actors)
		{
			stream.Write(actor->GetName());
			stream.Write(actor->IsActive());
			stream.Write(actor->IsCameraAttached());
			actor->SaveToFile(actorsFolder + actor->GetName() + ".actor");
		}
		stream.Write(data_field ? data_field->GetName() : "N\A");
		stream.Write(data_spawn ? data_spawn->GetName() : "N\A");
	}
	stream.Close();

}

void Scene::Update()
{
	camera->Update();

	backGround->GetComponent<Transform>()->SetPosition(Vector3(-camera->GetPosition().x, -camera->GetPosition().y, -10) / 80.0f);

	auto input = context->GetSubsystem<Input>();

	backGround->Update();
	for (auto actor : actors)
		actor->Update();
}

Actor* Scene::AddActor(Actor* actor)
{
	actors.emplace_back(actor); 
	if (actor->IsCameraAttached()) 
		camera->SetTransform(actor->GetComponent<Transform>());
	return actor;
}

Actor* Scene::AddActor(const std::string& path, const Vector3& pos)
{
	Actor* actor = CreateActor(path);
	if (actor->HasComponent<Transform>())
	{
		actor->GetComponent<Transform>()->SetPosition(pos);
		if (actor->HasComponent<RigidBody>())
			actor->GetComponent<RigidBody>()->GetBoundBox().Init(actor->GetComponent<Transform>());
	}
	actor->SetName(FileSystem::GetIntactFileNameFromPath(path));
	actor->SetActive(true);
	context->GetSubsystem<Renderer>()->UpdateActorList(actor);
	context->GetSubsystem<PhysicsManager>()->AddActor(actor);

	return actor;
}

void Scene::RemoveActor(Actor* var)
{
	for (auto iter = actors.begin(); iter != actors.end(); iter++) {
		if ((*iter)->GetName() == var->GetName()){
			actors.erase(iter);
			break;
		}
	}
}

Actor* Scene::FindActor(const std::string& name)
{
	for (auto iter = actors.begin(); iter != actors.end(); iter++) {
		if ((*iter)->GetName() == name) {
			return *iter;
		}
	}
	return nullptr;
}

Actor* Scene::CreateActor(const std::string& path)
{
	auto tmp = new Actor(context);
	if (path != NULL_STRING)
		tmp->LoadFromFile(path);

	actors.emplace_back(tmp);
	return actors.back();
}

Actor* Scene::DeleteActor(const std::string& name)
{
	for (auto iter = actors.begin(); iter != actors.end(); iter++) {
		if ((*iter)->GetName() == name) {
			Actor* result = *iter;
			actors.erase(iter);
			return result;
		}
	}
	return nullptr;
}

void Scene::SetDataField(Data_Field* data, const int& floor)
{
	data_field = data;
	camera->SetFieldData(data_field); 
	Init_Field_InstanceBuffer();
	backGround->GetComponent<Renderable>()->SetTexture(TextureType::Albedo, data_field->GetBackGroundPath(), data_field->GetBackGroundPath());

	for (int i = 0; i < data->_width * data->_height; i++)
	{
		switch (data->_blocks[i])
		{
		case 98000:
		{
			if (floor >= 16) continue;

			auto actor = AddActor("../../_Assets/Scene/Map/portal.actor", DataManager::BlockLocToBlockPos(data->_width, data->_height, i % data->_width, i / data->_height));
			auto data = new Data_Portal(this->GetName());
			data->_destPos = Vector3(0, -3000, 0);
			data->_destSceneName = "Floor" + std::to_string(floor + 1);
			dataManager->GetDatas(DataType::Portal)[data->GetName()] = data;
			actor->GetComponent<Controller>()->SetPortalData(data);
			break;
		}
		case 99000:
		{
			auto actor = AddActor("../../_Assets/Scene/NPC/Morian.actor", DataManager::BlockLocToBlockPos(data->_width, data->_height, i % data->_width, i / data->_height) + Vector3(0, 10.0f, 0));
			auto dataName = "Floor" + std::to_string(floor) + "Morian_Frame"; // "Floor1Morian_Frame.as"
			actor->GetComponent<Controller>()->SetDialogData(dataManager->GetData<Data_Dialog>(dataName));
			break;
		}
		case 99001:
		{
			auto actor = AddActor("../../_Assets/Scene/NPC/Cichol.actor", DataManager::BlockLocToBlockPos(data->_width, data->_height, i % data->_width, i / data->_height) + Vector3(0, 10.0f, 0));
			auto dataName = "Floor" + std::to_string(floor) + "Cichol_Frame"; // "Floor1Morian_Frame.as"
			actor->GetComponent<Controller>()->SetDialogData(dataManager->GetData<Data_Dialog>(dataName));
			break;
		}
		case 99002:
		{
			if (floor >= 16) continue;

			auto actor = AddActor("../../_Assets/Scene/NPC/Blony.actor", DataManager::BlockLocToBlockPos(data->_width, data->_height, i % data->_width, i / data->_height) + Vector3(0, 10.0f, 0));
			auto dataName = "Floor" + std::to_string(floor) + "Blony_Frame"; // "Floor1Morian_Frame.as"
			actor->GetComponent<Controller>()->SetDialogData(dataManager->GetData<Data_Dialog>(dataName));
			break;
		}
		case 99003:
		{
			if (floor >= 16) continue;

			auto actor = AddActor("../../_Assets/Scene/NPC/Fleta.actor", DataManager::BlockLocToBlockPos(data->_width, data->_height, i % data->_width, i / data->_height) + Vector3(0, 10.0f, 0));
			auto dataName = "Floor" + std::to_string(floor) + "Fleta_Frame"; // "Floor1Morian_Frame.as"
			actor->GetComponent<Controller>()->SetDialogData(dataManager->GetData<Data_Dialog>(dataName));
			break;
		}
		}
	}
}

VertexBuffer* Scene::GetInstanceBuffer(const BlockKind& var)
{
	if (field_instanceBuffer.find(var) != field_instanceBuffer.end())
		return field_instanceBuffer[var];
	else
		return nullptr;
}

void Scene::Init_Field_InstanceBuffer()
{
	for (auto data : field_geometry)
		SAFE_DELETE(data.second);

	for (auto buffer : field_instanceBuffer)
		SAFE_DELETE(buffer.second);

	field_geometry.clear();
	field_instanceBuffer.clear();

	for(auto& blockKind : dataManager->GetBlockKinds())  // 만약 블럭 추가하면 저것도 추가해야한다
	{
		VertexBuffer* buffer = new VertexBuffer(context);
		Geometry<VertexPositionScaleSprite>* geometry = new Geometry<VertexPositionScaleSprite>();

		field_instanceBuffer[blockKind] = buffer;
		field_geometry[blockKind] = geometry;
	}

	if (!data_field)
		return;

	int width = data_field->_width;
	int height = data_field->_height;
	
	SceneManager* sceneManager = context->GetSubsystem<SceneManager>();
	std::vector<BlockKind> blocks = data_field->_blocks;
	std::vector<BlockKind> _blocks_back = data_field->_blocks_back;
	std::vector<BlockKind> _blocks_front = data_field->_blocks_front;
	std::vector<BlockKind> _blocks_functional = data_field->_blocks_functional;
	BlockKind blockType0, blockType1, blockType2, blockType3;
	Vector3 blockType0_size, blockType1_size, blockType2_size, blockType3_size;

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			blockType0 = blocks[width * j + i];
			if (blockType0 >= 98000)
				continue;

			blockType0_size = sceneManager->GetBlock(blockType0)->GetComponent<Transform>()->GetScale();
			blockType1 = _blocks_back[width * j + i];
			blockType1_size = sceneManager->GetBlock(blockType1)->GetComponent<Transform>()->GetScale();
			blockType2 = _blocks_front[width * j + i];
			blockType2_size = sceneManager->GetBlock(blockType2)->GetComponent<Transform>()->GetScale();
			blockType3 = _blocks_functional[width * j + i];
			blockType3_size = sceneManager->GetBlock(blockType3)->GetComponent<Transform>()->GetScale();

			if (blockType0 != 0)
				field_geometry[blockType0]->AddVertex(VertexPositionScaleSprite(Vector3((-width / 2 + i) * BLOCK_SIZE, (-height / 2 + j) * BLOCK_SIZE, 0), blockType0_size, Vector2(0, 0)));
			if (blockType1 != 0)
				field_geometry[blockType1]->AddVertex(VertexPositionScaleSprite(Vector3((-width / 2 + i) * BLOCK_SIZE, (-height / 2 + j) * BLOCK_SIZE, 0), blockType1_size, Vector2(0, 0)));
			if (blockType2 != 0)
				field_geometry[blockType2]->AddVertex(VertexPositionScaleSprite(Vector3((-width / 2 + i) * BLOCK_SIZE, (-height / 2 + j) * BLOCK_SIZE, 0), blockType2_size, Vector2(0, 0)));
			if (blockType3 != 0)
				field_geometry[blockType3]->AddVertex(VertexPositionScaleSprite(Vector3((-width / 2 + i) * BLOCK_SIZE, (-height / 2 + j) * BLOCK_SIZE, 0), blockType3_size, Vector2(0, 0)));
		}
	}

	for (auto& blockType : dataManager->GetBlockKinds())
	{
		if (blockType == 0)
			continue;

		field_instanceBuffer[blockType]->Create<VertexPositionScaleSprite>(field_geometry[blockType]->GetVertices());
	}
}
