#include "Framework.h"
#include "ScriptManager.h"
#include <angelscript.h>
#include <AngelScript/scriptbuilder/scriptbuilder.h>

const bool ScriptManager::RegistEnum()
{
	int r;
	r = scriptEngine->RegisterEnum("KeyCode"); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "CLICK_LEFT", static_cast<unsigned long>(KeyCode::CLICK_LEFT)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "CLICK_RIGHT", static_cast<unsigned long>(KeyCode::CLICK_RIGHT)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_RIGHT", static_cast<unsigned long>(KeyCode::KEY_RIGHT)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_LEFT", static_cast<unsigned long>(KeyCode::KEY_LEFT)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_UP", static_cast<unsigned long>(KeyCode::KEY_UP)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_DOWN", static_cast<unsigned long>(KeyCode::KEY_DOWN)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_0", static_cast<unsigned long>(KeyCode::KEY_0)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_1", static_cast<unsigned long>(KeyCode::KEY_1)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_2", static_cast<unsigned long>(KeyCode::KEY_2)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_3", static_cast<unsigned long>(KeyCode::KEY_3)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_4", static_cast<unsigned long>(KeyCode::KEY_4)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_5", static_cast<unsigned long>(KeyCode::KEY_5)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_6", static_cast<unsigned long>(KeyCode::KEY_6)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_7", static_cast<unsigned long>(KeyCode::KEY_7)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_8", static_cast<unsigned long>(KeyCode::KEY_8)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_9", static_cast<unsigned long>(KeyCode::KEY_9)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_A", static_cast<unsigned long>(KeyCode::KEY_A)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_B", static_cast<unsigned long>(KeyCode::KEY_B)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_C", static_cast<unsigned long>(KeyCode::KEY_C)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_D", static_cast<unsigned long>(KeyCode::KEY_D)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_E", static_cast<unsigned long>(KeyCode::KEY_E)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_F", static_cast<unsigned long>(KeyCode::KEY_F)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_G", static_cast<unsigned long>(KeyCode::KEY_G)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_H", static_cast<unsigned long>(KeyCode::KEY_H)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_I", static_cast<unsigned long>(KeyCode::KEY_I)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_J", static_cast<unsigned long>(KeyCode::KEY_J)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_K", static_cast<unsigned long>(KeyCode::KEY_K)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_L", static_cast<unsigned long>(KeyCode::KEY_L)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_M", static_cast<unsigned long>(KeyCode::KEY_M)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_N", static_cast<unsigned long>(KeyCode::KEY_N)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_O", static_cast<unsigned long>(KeyCode::KEY_O)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_P", static_cast<unsigned long>(KeyCode::KEY_P)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_Q", static_cast<unsigned long>(KeyCode::KEY_Q)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_R", static_cast<unsigned long>(KeyCode::KEY_R)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_S", static_cast<unsigned long>(KeyCode::KEY_S)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_T", static_cast<unsigned long>(KeyCode::KEY_T)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_U", static_cast<unsigned long>(KeyCode::KEY_U)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_V", static_cast<unsigned long>(KeyCode::KEY_V)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_W", static_cast<unsigned long>(KeyCode::KEY_W)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_X", static_cast<unsigned long>(KeyCode::KEY_X)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_Y", static_cast<unsigned long>(KeyCode::KEY_Y)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_Z", static_cast<unsigned long>(KeyCode::KEY_Z)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_SHIFT", static_cast<unsigned long>(KeyCode::KEY_SHIFT)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_CONTROL", static_cast<unsigned long>(KeyCode::KEY_CONTROL)); assert(r >= 0);
	r = scriptEngine->RegisterEnumValue("KeyCode", "KEY_SPACE", static_cast<unsigned long>(KeyCode::KEY_SPACE)); assert(r >= 0);

	return true;
}

const bool ScriptManager::RegistType()
{
	int r = 0;
	r = scriptEngine->RegisterInterface("ScriptBehavior"); assert(r >= 0);

	//Subsystem
	r = scriptEngine->RegisterObjectType("Input", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Timer", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("DataManager", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("SceneManager", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("UIManager", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("GameManager", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("DialogManager", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("InventoryManager", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("MonsterManager", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);

	//Scene
	r = scriptEngine->RegisterObjectType("Actor", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Camera", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Transform", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Collider", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Renderable", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("RigidBody", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Animator", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Controller", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);

	//Resource
	r = scriptEngine->RegisterObjectType("Mesh", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Material", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);

	//Data
	r = scriptEngine->RegisterObjectType("Data_Charactor", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);

	//UI
	r = scriptEngine->RegisterObjectType("Frame", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Box", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("ProgressBar", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(r >= 0);


	//Value Type
	r = scriptEngine->RegisterObjectType("Vector2", sizeof(Vector2), asOBJ_VALUE | asOBJ_APP_CLASS | asOBJ_APP_CLASS_CONSTRUCTOR | asOBJ_APP_CLASS_COPY_CONSTRUCTOR | asOBJ_APP_CLASS_DESTRUCTOR); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Vector3", sizeof(Vector3), asOBJ_VALUE | asOBJ_APP_CLASS | asOBJ_APP_CLASS_CONSTRUCTOR | asOBJ_APP_CLASS_COPY_CONSTRUCTOR | asOBJ_APP_CLASS_DESTRUCTOR); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Vector4", sizeof(Vector4), asOBJ_VALUE | asOBJ_APP_CLASS | asOBJ_APP_CLASS_CONSTRUCTOR | asOBJ_APP_CLASS_COPY_CONSTRUCTOR | asOBJ_APP_CLASS_DESTRUCTOR); assert(r >= 0);
	r = scriptEngine->RegisterObjectType("Quaternion", sizeof(Quaternion), asOBJ_VALUE | asOBJ_APP_CLASS | asOBJ_APP_CLASS_CONSTRUCTOR | asOBJ_APP_CLASS_COPY_CONSTRUCTOR | asOBJ_APP_CLASS_DESTRUCTOR); assert(r >= 0);

	return true;
}

const bool ScriptManager::RegistSubsystem()
{
	int r;
	
	r = scriptEngine->RegisterGlobalProperty("Timer timer", context->GetSubsystem<Timer>()); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Timer", "float GetDeltaTime()", asMETHOD(Timer, GetDeltaTimeSec), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Timer", "float GetDeltaTimeMs()", asMETHOD(Timer, GetDeltaTimeMs), asCALL_THISCALL); assert(r >= 0);

	r = scriptEngine->RegisterGlobalProperty("Input input", context->GetSubsystem<Input>());
	r = scriptEngine->RegisterObjectMethod("Input", "const Vector2& GetMousePosition()", asMETHOD(Input, GetMousePosition), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Input", "const Vector2& GetMouseMoveValue()", asMETHOD(Input, GetMouseMoveVaule), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Input", "const bool KeyPress(const KeyCode& in)", asMETHOD(Input, KeyPress), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Input", "const bool KeyDown(const KeyCode& in)", asMETHOD(Input, KeyDown), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Input", "const bool KeyUp(const KeyCode& in)", asMETHOD(Input, KeyUp), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Input", "const bool KeyDoubleDown(const KeyCode& in)", asMETHOD(Input, KeyDoubleDown), asCALL_THISCALL); assert(r >= 0);

	r = scriptEngine->RegisterGlobalProperty("DataManager dataManager", context->GetSubsystem<DataManager>()); assert(r >= 0);
	r = scriptEngine->RegisterGlobalProperty("SceneManager sceneManager", context->GetSubsystem<SceneManager>()); assert(r >= 0);

	r = scriptEngine->RegisterGlobalProperty("UIManager uiManager", context->GetSubsystem<UIManager>()); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("UIManager", "Box &GetUIComponent_Box(const string& in)", asMETHOD(UIManager, GetUIComponent_Box), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("UIManager", "ProgressBar &GetUIComponent_ProgressBar(const string& in)", asMETHOD(UIManager, GetUIComponent_ProgressBar), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("UIManager", "void SetCurrentUI(const string& in)", asMETHOD(UIManager, SetCurrentUI), asCALL_THISCALL); assert(r >= 0);

	r = scriptEngine->RegisterGlobalProperty("GameManager gameManager", context->GetSubsystem<GameManager>()); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "Controller &GetProtagonist()", asMETHOD(GameManager, GetProtagonistController), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "string GetProtagonistLv()", asMETHOD(GameManager, GetProtagonistLv), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "string GetProtagonistMobName()", asMETHOD(GameManager, GetProtagonistMobName), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "void EnforceProtagonistJump()", asMETHOD(GameManager, EnforceProtagonistJump), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "void EnforceProtagonistSpeed()", asMETHOD(GameManager, EnforceProtagonistSpeed), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "void MainMenu_SetStack(int var)", asMETHOD(GameManager, MainMenu_SetStack), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "int MainMenu_GetStack()", asMETHOD(GameManager, MainMenu_GetStack), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "void MainMenu_Start()", asMETHOD(GameManager, MainMenu_Start), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "void MainMenu_Exit()", asMETHOD(GameManager, MainMenu_Exit), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "void LoadGame(int var)", asMETHOD(GameManager, LoadGame), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "void SaveGame(int var)", asMETHOD(GameManager, SaveGame), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "void Exit_To_MainMenu()", asMETHOD(GameManager, Exit_To_MainMenu), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "void NormalEnding()", asMETHOD(GameManager, NormalEnding), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "void TrueEnding()", asMETHOD(GameManager, TrueEnding), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("GameManager", "void SetGradiateTime(float time)", asMETHOD(GameManager, SetGradiateTime), asCALL_THISCALL); assert(r >= 0);

	r = scriptEngine->RegisterGlobalProperty("DialogManager dialogManager", context->GetSubsystem<DialogManager>()); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("DialogManager", "void DialogDefaultUpdate()", asMETHOD(DialogManager, DialogDefaultUpdate), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("DialogManager", "void DialogSetIllust(const string& in)", asMETHOD(DialogManager, DialogSetIllust), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("DialogManager", "void DialogSetName(const string& in)", asMETHOD(DialogManager, DialogSetName), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("DialogManager", "void DialogSetText(const string& in)", asMETHOD(DialogManager, DialogSetText), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("DialogManager", "void DialogSetButton(int index, const string& in)", asMETHOD(DialogManager, DialogSetButton), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("DialogManager", "bool IsDialogButtonClicked(int index)", asMETHOD(DialogManager, IsDialogButtonClicked), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("DialogManager", "void DialogSetScript(const string& in)", asMETHOD(DialogManager, DialogSetScript), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("DialogManager", "void DialogEnd()", asMETHOD(DialogManager, DialogEnd), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("DialogManager", "int DialogGetState()", asMETHOD(DialogManager, DialogGetState), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("DialogManager", "void DialogSetState(int var)", asMETHOD(DialogManager, DialogSetState), asCALL_THISCALL); assert(r >= 0);
	
	r = scriptEngine->RegisterGlobalProperty("InventoryManager inventoryManager", context->GetSubsystem<InventoryManager>()); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("InventoryManager", "void OpenInventory()", asMETHOD(InventoryManager, OpenInventory), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("InventoryManager", "void CloseInventory()", asMETHOD(InventoryManager, CloseInventory), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("InventoryManager", "void ToggleInventory()", asMETHOD(InventoryManager, ToggleInventory), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("InventoryManager", "bool InsertItem(int x, int y, const string& in, int amount)", asMETHOD(InventoryManager, InsertItem), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("InventoryManager", "bool InsertItemAuto(const string& in, int amount)", asMETHOD(InventoryManager, InsertItemAuto), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("InventoryManager", "void DeleteItem(int x, int y, int amount, int amount)", asMETHOD(InventoryManager, DeleteItem), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("InventoryManager", "void DeleteItemAuto(const string& in, int amount)", asMETHOD(InventoryManager, DeleteItem_Auto), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("InventoryManager", "int GetUsedItem()", asMETHOD(InventoryManager, GetUsedItem), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("InventoryManager", "int GetItemStock(const string& in)", asMETHOD(InventoryManager, GetItemStock), asCALL_THISCALL); assert(r >= 0);

	r = scriptEngine->RegisterGlobalProperty("MonsterManager monsterManager", context->GetSubsystem<MonsterManager>()); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("MonsterManager", "void SpawnAuto(const string& in, int team, bool isAgressive)", asMETHOD(MonsterManager, SpawnAuto), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("MonsterManager", "void ToggleEvolution()", asMETHOD(MonsterManager, ToggleEvolution), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("MonsterManager", "void Teleport(const string& in, const string& in, const Vector3& in)", asMETHOD(MonsterManager, Teleport), asCALL_THISCALL); assert(r >= 0);


	return true;
}

const bool ScriptManager::RegistActor()
{
	int r;

	r = scriptEngine->RegisterObjectMethod("Actor", "Actor &opAssign(const Actor &in)", asMETHODPR(Actor, operator =, (const Actor&), Actor&), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Actor", "const string& GetName()", asMETHOD(Actor, GetName), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Actor", "void SetName(const string& in)", asMETHOD(Actor, SetName), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Actor", "const bool& IsActive()", asMETHOD(Actor, IsActive), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Actor", "void SetIsActive(const bool& in)", asMETHOD(Actor, SetActive), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Actor", "Transform &GetTransform()", asMETHOD(Actor, GetComponent<Transform>), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Actor", "Renderable &GetRenderable()", asMETHOD(Actor, GetComponent<Renderable>), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Actor", "RigidBody &GetRigidBody()", asMETHOD(Actor, GetComponent<RigidBody>), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Actor", "Animator &GetAnimator()", asMETHOD(Actor, GetComponent<Animator>), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Actor", "Controller &GetController()", asMETHOD(Actor, GetComponent<Controller>), asCALL_THISCALL); assert(r >= 0);

	return true;
}

const bool ScriptManager::RegistSceneComponent()
{
	int r;
	//Transform
	r = scriptEngine->RegisterObjectMethod("Transform", "Transform &opAssign(const Transform &in)", asMETHODPR(Transform, operator =, (const Transform&), Transform&), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "const Vector3& GetLocalScale()", asMETHOD(Transform, GetLocalScale), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "void SetLocalScale(const Vector3& in)", asMETHOD(Transform, SetLocalScale), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "const Quaternion& GetLocalRotation()", asMETHOD(Transform, GetLocalRotation), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "void SetLocalRotation(const Quaternion& in)", asMETHOD(Transform, SetLocalRotation), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "const Vector3& GetLocalPosition()", asMETHOD(Transform, GetLocalPosition), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "void SetLocalPosition(const Vector3& in)", asMETHOD(Transform, SetLocalPosition), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "const Vector3 GetScale()", asMETHOD(Transform, GetScale), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "void SetScale(const Vector3& in)", asMETHOD(Transform, SetScale), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "const Quaternion GetRotation()", asMETHOD(Transform, GetRotation), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "void SetRotation(const Quaternion& in)", asMETHOD(Transform, SetRotation), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "const Vector3 GetPosition()", asMETHOD(Transform, GetPosition), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "void SetPosition(const Vector3& in)", asMETHOD(Transform, SetPosition), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "Transform& GetRoot()", asMETHOD(Transform, GetRoot), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Transform", "Transform& GetParent()", asMETHOD(Transform, GetParent), asCALL_THISCALL); assert(r >= 0);

	// Renderable
	r = scriptEngine->RegisterObjectMethod("Renderable", "Renderable &opAssign(const Renderable &in)", asMETHODPR(Renderable, operator =, (const Renderable&), Renderable&), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Renderable", "Mesh& GetMesh()", asMETHOD(Renderable, GetMesh), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Renderable", "Material& GetMaterial()", asMETHOD(Renderable, GetMaterial), asCALL_THISCALL); assert(r >= 0);

	// RigidBody
	r = scriptEngine->RegisterObjectMethod("RigidBody", "Renderable &opAssign(const RigidBody &in)", asMETHODPR(RigidBody, operator =, (const RigidBody&), RigidBody&), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("RigidBody", "void AddMoveVector(const float x, const float y)", asMETHOD(RigidBody, AddMoveVectorFloat), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("RigidBody", "void Jump(const Vector3 &in)", asMETHOD(RigidBody, Jump), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("RigidBody", "void Move(const Vector3 &in)", asMETHOD(RigidBody, Move), asCALL_THISCALL); assert(r >= 0);

	// Animator
	r = scriptEngine->RegisterObjectMethod("Animator", "Animator &opAssign(const Animator &in)", asMETHODPR(Animator, operator =, (const Animator&), Animator&), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Animator", "void SetAnimation(const string &in)", asMETHOD(Animator, SetAnimation_Script), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Animator", "void SetReversed(const bool &in)", asMETHOD(Animator, SetReversed), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Animator", "bool IsReversed()", asMETHOD(Animator, IsReversed), asCALL_THISCALL); assert(r >= 0);

	// Controller
	r = scriptEngine->RegisterObjectMethod("Controller", "Controller &opAssign(const Controller &in)", asMETHODPR(Controller, operator =, (const Controller&), Controller&), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Stand()", asMETHOD(Controller, Stand), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Walk(const int& in)", asMETHOD(Controller, Walk), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Run(const int& in)", asMETHOD(Controller, Run), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Jump()", asMETHOD(Controller, Jump), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Gaurd()", asMETHOD(Controller, Gaurd), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Attack1()", asMETHOD(Controller, Attack1), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Attack2()", asMETHOD(Controller, Attack2), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Die()", asMETHOD(Controller, Die), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void SuperJump(const int& in)", asMETHOD(Controller, SuperJump), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Heal(const int& in, const int& in, const int& in)", asMETHOD(Controller, Heal), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Portal()", asMETHOD(Controller, Portal), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Dialog()", asMETHOD(Controller, Dialog), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void Evolution(const string& in)", asMETHOD(Controller, Evolution), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void RandomWalk(float x)", asMETHOD(Controller, RandomWalk), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void RandomRun(float x)", asMETHOD(Controller, RandomRun), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void RandomAttack(float x, float percent1, float percent2, float percent3)", asMETHOD(Controller, RandomAttack), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "bool IsHostile()", asMETHOD(Controller, IsHostile), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void ObtainExp(const int& in)", asMETHOD(Controller, ObtainExp), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void RandomSkillChange()", asMETHOD(Controller, RandomSkillChange), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Controller", "void RandomRGBChange()", asMETHOD(Controller, RandomRGBChange), asCALL_THISCALL); assert(r >= 0);

	return true;
}

//Constructor
void ConstructorVector2(Vector2* self)
{
	new(self) Vector2(0, 0);
}

void ConstructorVector3(Vector3* self)
{
	new(self) Vector3(0, 0, 0);
}

void ConstructorVector4(Vector4* self)
{
	new(self) Vector4(0, 0, 0, 0);
}

void ConstructorQuaternion(Quaternion* self)
{
	new(self) Quaternion(0, 0, 0, 0);
}

//CopyConstructor
void CopyConstructorVector2(const Vector2& other, Vector2* self)
{
	new(self) Vector2(other.x, other.y);
}

void CopyConstructorVector3(const Vector3& other, Vector3* self)
{
	new(self) Vector3(other.x, other.y, other.z);
}

void CopyConstructorVector4(const Vector4& other, Vector4* self)
{
	new(self) Vector4(other.x, other.y, other.z, other.w);
}

void CopyConstructorQuaternion(const Quaternion& other, Quaternion* self)
{
	new(self) Quaternion(other.x, other.y, other.z, other.w);
}

//Constructor float
void ConstructorVector2Floats(float x, float y, Vector2* self)
{
	new(self) Vector2(x, y);
}

void ConstructorVector3Floats(float x, float y, float z, Vector2* self)
{
	new(self) Vector3(x, y, z);
}

void ConstructorVector4Floats(float x, float y, float z, float w, Vector2* self)
{
	new(self) Vector4(x, y, z, w);
}

void ConstructorQuaternionFloats(float x, float y, float z, float w, Quaternion* self)
{
	new(self) Quaternion(x, y, z, w);
}

//Destructor
void DestructVector2(Vector2* self)
{
	self->~Vector2();
}

void DestructVector3(Vector3* self)
{
	self->~Vector3();
}

void DestructVector4(Vector4* self)
{
	self->~Vector4();
}

void DestructQuaternion(Quaternion* self)
{
	self->~Quaternion();
}

//Assignment
static Vector2& Vector2Assignment(const Vector2& other, Vector2* self)
{
	return *self = other;
}

static Vector3& Vector3Assignment(const Vector3& other, Vector3* self)
{
	return *self = other;
}

static Vector4& Vector4Assignment(const Vector4& other, Vector4* self)
{
	return *self = other;
}

static Quaternion& QuaternionAssignment(const Quaternion& other, Quaternion* self)
{
	return *self = other;
}


//AddFunction
static Vector2 Vector2AddVector2(const Vector2& other, Vector2* self)
{
	return *self + other;
}

static Vector3 Vector3AddVector3(const Vector3& other, Vector3* self)
{
	return *self + other;
}

static Vector4 Vector4AddVector4(const Vector4& other, Vector4* self)
{
	return *self + other;
}

// Substract 
static Vector2 Vector2SubVector2(const Vector2& other, Vector2* self)
{
	return *self - other;
}

static Vector3 Vector3SubVector3(const Vector3& other, Vector3* self)
{							  
	return *self - other;	  
}							  
							  
static Vector4 Vector4SubVector4(const Vector4& other, Vector4* self)
{
	return *self - other;
}

// Multiply
static Vector2 Vector2MulFloat(float value, Vector2* self)
{
	return *self * value;
}

static Vector3 Vector3MulFloat(float value, Vector3* self)
{
	return *self * value;
}

static Vector4 Vector4MulFloat(float value, Vector4* self)
{
	return *self * value;
}

static Quaternion QuaternionMulFloat(float value, Quaternion* self)
{
	return *self * value;
}

const bool ScriptManager::RegistValueType()
{
	// operator overloads http://www.angelcode.com/angelscript/sdk/docs/manual/doc_script_class_ops.html
	
	int r;
	//Vector2
	r = scriptEngine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructorVector2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(const Vector2 &in)", asFUNCTION(CopyConstructorVector2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Vector2", asBEHAVE_CONSTRUCT, "void f(float, float)", asFUNCTION(ConstructorVector2Floats), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Vector2", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVector2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector2", "Vector2 &opAssign(const Vector2 &in)", asFUNCTION(Vector2Assignment), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector2", "Vector2 opAdd(const Vector2 &in)", asFUNCTION(Vector2AddVector2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector2", "Vector2 opSub(const Vector2 &in)", asFUNCTION(Vector2SubVector2), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector2", "Vector2 opMul(float)", asFUNCTION(Vector2MulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector2", "Vector2 opMul_r(float)", asFUNCTION(Vector2MulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Vector2", "float x", asOFFSET(Vector2, x));
	r = scriptEngine->RegisterObjectProperty("Vector2", "float y", asOFFSET(Vector2, y));

	//Vector3
	r = scriptEngine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructorVector3), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(const Vector3 &in)", asFUNCTION(CopyConstructorVector3), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Vector3", asBEHAVE_CONSTRUCT, "void f(float, float, float)", asFUNCTION(ConstructorVector3Floats), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Vector3", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVector3), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector3", "Vector3 &opAssign(const Vector3 &in)", asFUNCTION(Vector3Assignment), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opAdd(const Vector3 &in)", asFUNCTION(Vector3AddVector3), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opSub(const Vector3 &in)", asFUNCTION(Vector3SubVector3), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opMul(float)", asFUNCTION(Vector3MulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector3", "Vector3 opMul_r(float)", asFUNCTION(Vector3MulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Vector3", "float x", asOFFSET(Vector3, x)); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Vector3", "float y", asOFFSET(Vector3, y)); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Vector3", "float z", asOFFSET(Vector3, z)); assert(r >= 0);

	//Vector4
	r = scriptEngine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructorVector4), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(const Vector4 &in)", asFUNCTION(CopyConstructorVector4), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Vector4", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructorVector4Floats), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Vector4", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructVector4), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector4", "Vector4 &opAssign(const Vector4 &in)", asFUNCTION(Vector4Assignment), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector4", "Vector4 opAdd(const Vector4 &in)", asFUNCTION(Vector4AddVector4), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector4", "Vector4 opSub(const Vector4 &in)", asFUNCTION(Vector4SubVector4), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector4", "Vector4 opMul(float)", asFUNCTION(Vector4MulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Vector4", "Vector4 opMul_r(float)", asFUNCTION(Vector4MulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Vector4", "float x", asOFFSET(Vector4, x)); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Vector4", "float y", asOFFSET(Vector4, y)); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Vector4", "float z", asOFFSET(Vector4, z)); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Vector4", "float w", asOFFSET(Vector4, w)); assert(r >= 0);

	//Quaternion
	r = scriptEngine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructorQuaternion), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(const Quaternion &in)", asFUNCTION(CopyConstructorQuaternion), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Quaternion", asBEHAVE_CONSTRUCT, "void f(float, float, float, float)", asFUNCTION(ConstructorQuaternionFloats), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectBehaviour("Quaternion", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructQuaternion), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Quaternion", "Quaternion &opAssign(const Quaternion &in)", asFUNCTION(QuaternionAssignment), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Quaternion", "Quaternion opMul(float)", asFUNCTION(QuaternionMulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Quaternion", "Quaternion opMul_r(float)", asFUNCTION(QuaternionMulFloat), asCALL_CDECL_OBJLAST); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Quaternion", "float x", asOFFSET(Quaternion, x)); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Quaternion", "float y", asOFFSET(Quaternion, y)); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Quaternion", "float z", asOFFSET(Quaternion, z)); assert(r >= 0);
	r = scriptEngine->RegisterObjectProperty("Quaternion", "float w", asOFFSET(Quaternion, w)); assert(r >= 0);

	return true;
}

const bool ScriptManager::RegistUI()
{
	//Text
	int r;

	r = scriptEngine->RegisterObjectMethod("Frame", "Frame &opAssign(const Frame &in)", asMETHODPR(UIWidgetFrame, operator =, (const UIWidgetFrame&), UIWidgetFrame&), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Frame", "void SetText(const string &in)", asMETHOD(UIWidgetFrame, SetTextFromMultibyte), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Frame", "bool IsClicked()", asMETHOD(UIWidgetFrame, IsClicked), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Frame", "bool IsCovered()", asMETHOD(UIWidgetFrame, IsCovered), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Frame", "Vector3 GetPosition()", asMETHOD(UIWidgetFrame, GetPosition), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Frame", "void SetPosition(const Vector3 &in)", asMETHOD(UIWidgetFrame, SetPosition), asCALL_THISCALL); assert(r >= 0);

	r = scriptEngine->RegisterObjectMethod("Box", "Box &opAssign(const Box &in)", asMETHODPR(Box, operator =, (const Box&), Box&), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Box", "void SetVisible(const bool &in)", asMETHOD(Box, SetVisible), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Box", "Vector3 GetPosition()", asMETHOD(Box, GetPosition), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("Box", "void SetPosition(const Vector3 &in)", asMETHOD(Box, SetPosition), asCALL_THISCALL); assert(r >= 0);

	r = scriptEngine->RegisterObjectMethod("ProgressBar", "ProgressBar &opAssign(const ProgressBar &in)", asMETHODPR(ProgressBar, operator =, (const ProgressBar&), ProgressBar&), asCALL_THISCALL); assert(r >= 0);
	r = scriptEngine->RegisterObjectMethod("ProgressBar", "void SetVisible(int numerator, int denominator)", asMETHOD(ProgressBar, SetProgress), asCALL_THISCALL); assert(r >= 0);

	return true;
}
