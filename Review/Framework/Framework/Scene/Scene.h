#pragma once

enum class SceneLayer : uint
{
	Back,
	Default,
	Function,
	Front
};

class Scene
{
public:
	static std::string defaultDir;
	static std::string blocksDir;

private:
	friend class SceneManager; friend class GameManager;

protected:
	Scene(class Context* context);
	~Scene();

	void LoadFromFile(const std::string& path);
	void SaveToFile(const std::string& path);

	void Update();

public:
	Camera* GetCamera() { return camera; }

	const std::vector<Actor*>& GetActors() { return actors; }
	Actor* AddActor(Actor* actor);
	Actor* AddActor(const std::string& name, const Vector3& pos);

	void RemoveActor(Actor* var);
	
	Actor* FindActor(const std::string& name);
	Actor* CreateActor(const std::string& path = NULL_STRING);
	Actor* DeleteActor(const std::string& name);

	const std::string& GetName() const { return name; }
	void SetName(const std::string& name) { this->name = name; }

	const std::string& GetDefaultDirectory() { return defaultDir; }

	Actor* GetBackGround() { return backGround; }
	void SetBackGround(Actor* actor) { backGround = actor; }

	class Data_Field* GetDataField() { return data_field; }
	void SetDataField(Data_Field* data, const int& floor = 1);

	class Data_Spawn* GetDataSpawn() { return data_spawn; }
	void SetDataSpawn(Data_Spawn* data) { this->data_spawn = data; }

	class VertexBuffer* GetInstanceBuffer(const BlockKind& var);

public:
	void Init_Field_InstanceBuffer();

protected:
	class Context* context;
	class Camera* camera;
	class DataManager* dataManager;
	class PhysicsManager* physicsManager;

	class Data_Field* data_field;
	class Data_Spawn* data_spawn;

	std::vector<class Actor*> actors;
	class Actor* backGround;
	std::map<BlockKind, class VertexBuffer*> field_instanceBuffer;
	std::map<BlockKind, Geometry<VertexPositionScaleSprite>*> field_geometry;

	std::string name = "";

	bool bEditorMode = false;
	bool bAdded;
};