#include "stdafx.h"
#include "Widget_Hierarchy.h"

Widget_Hierarchy::Widget_Hierarchy(Context * context)
	: IWidget(context)
{
	title = "Hierarchy";
	sceneManager = context->GetSubsystem<SceneManager>();
	dataManager = context->GetSubsystem<DataManager>();
	renderer = context->GetSubsystem<Renderer>();

	ZeroMemory(&clicked_data, sizeof(clicked_data));
}

void Widget_Hierarchy::Render()
{
	if (!bVisible)
		return;

	clicked_data.isSelectedScene = false;
	clicked_data.scope = Hierarchy_ClickedScope::None;

	ShowHierarchy();

	UpdateClickedData(Hierarchy_ClickedScope::Window);

	// Imgui°¡ Tree °°Àº ±¸Á¶ ³»ºÎ¿¡¼­ ÆË¾÷ ¶ß°Ô°¡ ¾ÈµÊ
	if (ImGui::GetIO().MouseDown[1])
	{
		switch (clicked_data.scope)
		{
		case Hierarchy_ClickedScope::Component:
			ImGui::OpenPopup("Hierarchy Component Popup");
			break;
		case Hierarchy_ClickedScope::Actor:
			ImGui::OpenPopup("Hierarchy Actor Popup");
			break;
		case Hierarchy_ClickedScope::Scene:
			ImGui::OpenPopup("Hierarchy Scene Popup");
			break;
		case Hierarchy_ClickedScope::Window:
			ImGui::OpenPopup("Hierarchy Window Popup");
			break;
		}
	}

	RightClickForComponent();
	RightClickForActor();
	RightClickForScene();
	RightClickForWindow();

	if(clicked_data.scope != Hierarchy_ClickedScope::None)
		clicked_data.scope_before = clicked_data.scope;
}

void Widget_Hierarchy::ShowHierarchy()
{
	auto scenes = sceneManager->GetScenes();

	for (auto& scene : scenes)
		AddSceneInHierarchy(scene.second);
}

void Widget_Hierarchy::AddSceneInHierarchy(Scene * scene)
{
	if (!scene)
		return;

	std::vector<Actor*> actors = scene->GetActors();

	if (ImGui::CollapsingHeader(scene->GetName().c_str()))
	{
		if (clicked_data.isSelectedScene)
			return;

		EditorHelper::Get()->SelectScene(scene);
		if( !sceneManager->GetCurrentScene() || sceneManager->GetCurrentScene()->GetName() != scene->GetName())
			sceneManager->SetCurrentScene(scene->GetName());

		UpdateClickedData(Hierarchy_ClickedScope::Scene);

		EditorHelper::Get()->SelectActor(nullptr);
		for (auto& actor : actors)
			AddActorInHierarchy(actor);

		return;
	}

	return;
}

void Widget_Hierarchy::AddActorInHierarchy(Actor * actor)
{
	if (!actor)
		return;

	std::string nodeName = actor->GetName() == "" ? "No Name" : actor->GetName();

	if (ImGui::TreeNodeEx(nodeName.c_str(), GetTreeNodeFlags(Hierarchy_ClickedScope::Actor, actor)))
	{
		EditorHelper::Get()->SelectActor(actor);
		
		UpdateClickedData(Hierarchy_ClickedScope::Actor, actor);

		auto renderable = actor->GetComponent<Renderable>();
		if (renderable) {
			if (ImGui::TreeNodeEx(reinterpret_cast<void*>(renderable->GetID()), GetTreeNodeFlags(Hierarchy_ClickedScope::Component, actor, ComponentType::Renderable), "Renderable"))
			{
				UpdateClickedData(Hierarchy_ClickedScope::Component, actor, ComponentType::Renderable);
				ImGui::TreePop();
			}
		}
		
		auto animator = actor->GetComponent<Animator>();
		if (animator) {
			if (ImGui::TreeNodeEx(reinterpret_cast<void*>(animator->GetID()), GetTreeNodeFlags(Hierarchy_ClickedScope::Component, actor, ComponentType::Animator), "Animator"))
			{
				UpdateClickedData(Hierarchy_ClickedScope::Component, actor,  ComponentType::Animator);
				ImGui::TreePop();
			}
		}
		auto transform = actor->GetComponent<Transform>();
		if (transform) {
			if (ImGui::TreeNodeEx(reinterpret_cast<void*>(transform->GetID()), GetTreeNodeFlags(Hierarchy_ClickedScope::Component, actor, ComponentType::Transform), "Transform"))
			{
				UpdateClickedData(Hierarchy_ClickedScope::Component, actor, ComponentType::Transform);
				ImGui::TreePop();
			}
		}
		auto rigidBody = actor->GetComponent<RigidBody>();
		if (rigidBody) {
			if (ImGui::TreeNodeEx(reinterpret_cast<void*>(rigidBody->GetID()), GetTreeNodeFlags(Hierarchy_ClickedScope::Component, actor, ComponentType::RigidBody), "RigidBody"))
			{
				UpdateClickedData(Hierarchy_ClickedScope::Component, actor, ComponentType::RigidBody);
				ImGui::TreePop();
			}
		}

		auto scripter = actor->GetComponent<Scripter>();
		if (scripter) {
			if (ImGui::TreeNodeEx(reinterpret_cast<void*>(scripter->GetID()), GetTreeNodeFlags(Hierarchy_ClickedScope::Component, actor, ComponentType::Scripter), "Scripter"))
			{
				UpdateClickedData(Hierarchy_ClickedScope::Component, actor, ComponentType::Scripter);
				ImGui::TreePop();
			}
		}
		
		auto controller = actor->GetComponent<Controller>();
		if (controller) {
			if (ImGui::TreeNodeEx(reinterpret_cast<void*>(controller->GetID()), GetTreeNodeFlags(Hierarchy_ClickedScope::Component, actor, ComponentType::Controller), "Controller"))
			{
				UpdateClickedData(Hierarchy_ClickedScope::Component, actor, ComponentType::Controller);
				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}
}

void Widget_Hierarchy::UpdateClickedData(const Hierarchy_ClickedScope& scope, Actor* actor, const ComponentType& type)
{
	if (clicked_data.scope > scope)
		return;

	switch (scope)
	{
	case Hierarchy_ClickedScope::Scene:
		clicked_data.isSelectedScene = true;
		break;
	case Hierarchy_ClickedScope::Window:
		if (ImGui::IsWindowHovered())
			if (ImGui::GetIO().MouseDown[1])
			{
				clicked_data.scope = scope;
				clicked_data.actor = actor;
				clicked_data.type = type;
			}
		break;
	default:
		if (ImGui::IsItemHovered())
			if (ImGui::GetIO().MouseDown[1] || ImGui::GetIO().MouseDown[0])
			{
				clicked_data.scope = scope;
				clicked_data.actor = actor;
				clicked_data.type = type;
			}
		break;
	}
}

const ImGuiTreeNodeFlags Widget_Hierarchy::GetTreeNodeFlags(const Hierarchy_ClickedScope& scope, Actor* actor, const ComponentType& type)
{
	ImGuiTreeNodeFlags flags = 0;

	if (scope == Hierarchy_ClickedScope::Component)
		flags |= ImGuiTreeNodeFlags_Leaf;

	if (clicked_data.actor && clicked_data.scope_before == scope && clicked_data.actor->GetName() == actor->GetName() && clicked_data.type == type)
		flags |= ImGuiTreeNodeFlags_Selected;

	return flags;
}

void Widget_Hierarchy::RightClickForWindow()
{
	if (ImGui::BeginPopup("Hierarchy Window Popup"))
	{
		if (ImGui::MenuItem("Copy"))
		{
		}
		if (ImGui::MenuItem("Delete"))
		{

		}
		if (ImGui::MenuItem("Empty Scene"))
		{
			CreateScene();
		}

		ImGui::EndPopup();
	}
}

void Widget_Hierarchy::RightClickForScene()
{
	if (ImGui::BeginPopup("Hierarchy Scene Popup"))
	{
		if (ImGui::MenuItem("Copy")) 
		{

		}
		if (ImGui::MenuItem("Delete"))
		{

		}
		if (ImGui::MenuItem("Empty Actor"))
		{
			auto actor = CreateEmptyActor();
			if (actor)
			{
				static int tmp = 0;
				tmp += 1;
				actor->SetActive(true);
				actor->SetName("aaa" + std::to_string(tmp));
				context->GetSubsystem<Renderer>()->UpdateActorList(actor);
			}
		}
		if (ImGui::BeginMenu("Create2D"))
		{
			ImGui::EndMenu();
		}

		ImGui::EndPopup();
	}
}

void Widget_Hierarchy::RightClickForActor()
{
	if (ImGui::BeginPopup("Hierarchy Actor Popup"))
	{
		if (ImGui::BeginMenu("Create"))
		{
			Actor* actor = clicked_data.actor;
			if (actor)
			{
				if (ImGui::MenuItem("Rendererable")) 
				{
					if (actor->HasComponent<Renderable>())
					{
						ImGui::EndMenu();
						ImGui::EndPopup();
						return;
					}

					actor->AddComponent<Renderable>();
					context->GetSubsystem<Renderer>()->UpdateActorList(actor);
				}
				if (ImGui::MenuItem("Animator"))
				{
					if (actor->HasComponent<Animator>() || !actor->HasComponent<Renderable>())
					{
						ImGui::EndMenu();
						ImGui::EndPopup();
						return;
					}

					Animator* animator = actor->AddComponent<Animator>();
					animator->SetAnimation("Idle.anim", "Idle", actor->GetComponent<Renderable>());
					animator->Play();
					context->GetSubsystem<Renderer>()->UpdateActorList(actor);
				}
				if (ImGui::MenuItem("Transform"))
				{
					if (actor->HasComponent<Transform>())
					{
						ImGui::EndMenu();
						ImGui::EndPopup();
						return;
					}

					Transform* transform = actor->AddComponent<Transform>();
					transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
					transform->SetRotation(Quaternion(0.0f, 0.0f, 0.0f, 1.0f));
					transform->SetScale(Vector3(0.5f, 0.5f, 0.0f));
					context->GetSubsystem<Renderer>()->UpdateActorList(actor);
				}
				if (ImGui::MenuItem("RigidBody"))
				{
					if (actor->HasComponent<RigidBody>() || !actor->HasComponent<Transform>())
					{
						ImGui::EndMenu();
						ImGui::EndPopup();
						return;
					}

					RigidBody* rigidBody = actor->AddComponent<RigidBody>();
					rigidBody->SetBoundBoxAndTransform(actor->GetComponent<Transform>());
					rigidBody->SetRigidBodyType(RigidBodyType::Character);
					context->GetSubsystem<Renderer>()->UpdateActorList(actor);
					context->GetSubsystem<PhysicsManager>()->AddActor(actor);
				}
				if (ImGui::MenuItem("Scripter"))
				{
					if (actor->HasComponent<Scripter>() || !actor->HasComponent<Controller>())
					{
						ImGui::EndMenu();
						ImGui::EndPopup();
						return;
					}

					Scripter* scripter = actor->AddComponent<Scripter>();
					context->GetSubsystem<Renderer>()->UpdateActorList(actor);
				}
				if (ImGui::MenuItem("Controller"))
				{
					if (actor->HasComponent<Controller>())
					{
						ImGui::EndMenu();
						ImGui::EndPopup();
						return;
					}

					Controller* controller = actor->AddComponent<Controller>();
					controller->SetActor(actor);
					controller->SetMobData(dataManager->GetData<Data_Mob>("Ex"));
					controller->SetAttack1Data(dataManager->GetData<Data_Skill>("Ex"));
					controller->SetAttack2Data(dataManager->GetData<Data_Skill>("Ex"));
					controller->SetGuardData(dataManager->GetData<Data_Skill>("Ex"));
					context->GetSubsystem<Renderer>()->UpdateActorList(actor);
				}
			}
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Delete"))
		{
			Actor* actor = clicked_data.actor;
			sceneManager->GetCurrentScene()->RemoveActor(actor);
		}

		ImGui::EndPopup();
	}
}

void Widget_Hierarchy::RightClickForComponent()
{
	if (ImGui::BeginPopup("Hierarchy Component Popup"))
	{
		if (ImGui::MenuItem("Copy"))
		{

		}
		if (ImGui::MenuItem("Delete"))
		{
			switch (clicked_data.type)
			{
			case ComponentType::Renderable:
				clicked_data.actor->EraseComponent<Renderable>();
				break;
			case ComponentType::Animator:
				clicked_data.actor->EraseComponent<Animator>();
				break;
			case ComponentType::AudioResource:
				clicked_data.actor->EraseComponent<AudioSource>();
				break;
			case ComponentType::RigidBody:
				clicked_data.actor->EraseComponent<RigidBody>();
				break;
			case ComponentType::Scripter:
				clicked_data.actor->EraseComponent<Scripter>();
				break;
			}

			context->GetSubsystem<Renderer>()->UpdateActorList(clicked_data.actor);

		}

		ImGui::EndPopup();
	}
}

Scene* Widget_Hierarchy::CreateScene()
{
	sceneManager->CreateScene();

	return sceneManager->GetCurrentScene();
}

Actor * Widget_Hierarchy::CreateEmptyActor()
{
	auto scene = sceneManager->GetCurrentScene();
	if (scene)
	{
		Actor* actor = scene->CreateActor();
		renderer->UpdateActorList(actor);
		return actor;
	}
	return nullptr;
}

void Widget_Hierarchy::AddComponentToActor(const std::string & name)
{
}

void Widget_Hierarchy::SetComponentOfActor(const std::string & name)
{
}
