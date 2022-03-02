#include "stdafx.h"
#include "Widget_Inspector.h"
#include "./ImGui/Source/imgui.h"

Widget_Inspector::Widget_Inspector(Context * context)
	: IWidget(context)
{
	title = "Inspector";
	stringsForSamplerCombobox = { "clamp_point", "clamp_bilinear", "wrap_bilinear", "wrap_trilinear", "wrap_anisotropic" };
	stringsForRigidBodyType = { "UnMovable", "Movable", "Character", "Overlap" };
}

Widget_Inspector::~Widget_Inspector()
{
}

void Widget_Inspector::Render()
{
	if (!bVisible)
		return;

	ShowRenderer(context->GetSubsystem<Renderer>());
	ShowScene(context->GetSubsystem<SceneManager>()->GetCurrentScene());

	if (auto actor = EditorHelper::Get()->GetSelectedActor())
	{
		ShowActor(actor);
		ShowTransform(actor->GetComponent<Transform>());
		ShowRenderable(actor->GetComponent<Renderable>());
		ShowAnimator(actor->GetComponents<Animator>(), actor);
		ShowRigidBody(actor->GetComponent<RigidBody>());
		ShowScripter(actor->GetComponent<Scripter>(), actor);
		ShowController(actor->GetComponent<Controller>());
	}
}

void Widget_Inspector::ShowRenderer(Renderer* renderer)
{
	if (ImGui::CollapsingHeader("Renderer", ImGuiTreeNodeFlags_DefaultOpen)) {

		uint postprocessFlags = renderer->GetPostprocessFlags();
		uint rendererFlags = renderer->GetRendererFlags();
		float bloomIntensity = renderer->GetBloomIntensity();
		float blurSigma = renderer->GetBlurSigma();
		float blurStride = renderer->GetBlurStride();

		ImGui::CheckboxFlags("RendererFlags: showActorFrame", &rendererFlags, RendererFlags::GBuffer_Show_RigidBody);
		ImGui::CheckboxFlags("Postprocess: DownSample", &postprocessFlags, PostprocessFlag::DownSample);
		ImGui::CheckboxFlags("Postprocess: Bright", &postprocessFlags, PostprocessFlag::Bright);
		ImGui::CheckboxFlags("Postprocess: GaussianBlur", &postprocessFlags, PostprocessFlag::GaussianBlur);
		ImGui::CheckboxFlags("Postprocess: UpSample1", &postprocessFlags, PostprocessFlag::Upsample1);
		ImGui::CheckboxFlags("Postprocess: UpSample2", &postprocessFlags, PostprocessFlag::Upsample2);
		ImGui::CheckboxFlags("Postprocess: Blending", &postprocessFlags, PostprocessFlag::Blending);
		
		ImGui::TextUnformatted("BlurIntensity");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat("##BloomIntensity", &bloomIntensity, 0.0f, 0.1f, "%.3f", ImGuiInputTextFlags_CharsDecimal);

		ImGui::TextUnformatted("BlurSigma");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat("##BlurSigma", &blurSigma, 0.0f, 0.1f, "%.3f", ImGuiInputTextFlags_CharsDecimal);

		ImGui::TextUnformatted("BlurStride");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat("##BlurStride", &blurStride, 0.0f, 0.1f, "%.3f", ImGuiInputTextFlags_CharsDecimal);

		if (rendererFlags != renderer->GetRendererFlags()) renderer->SetRendererFlags(rendererFlags);
		if (postprocessFlags != renderer->GetPostprocessFlags()) renderer->SetPostprocessFlags(postprocessFlags);
		if (bloomIntensity != renderer->GetBloomIntensity()) renderer->SetBloomIntensity(bloomIntensity);
		if (blurSigma != renderer->GetBlurSigma()) renderer->SetBlurSigma(blurSigma);
		if (blurStride != renderer->GetBlurStride()) renderer->SetBlurStride(blurStride);
	}
}

void Widget_Inspector::ShowScene(Scene* scene)
{
	if (!scene)
		return;

	if (ImGui::CollapsingHeader("Scene", ImGuiTreeNodeFlags_DefaultOpen)) {

		if (ImGui::Button("Reflesh This Scene"))
		{
			context->GetSubsystem<Renderer>()->AcquireScene(scene);
			context->GetSubsystem<PhysicsManager>()->AcquireScene(scene);
		}

		static int tmp_index = 0;
		ImGui::InputInt("Actor for Effect Index", &tmp_index);
		if (ImGui::Button("Select BackGround"))
			EditorHelper::Get()->SelectActor(scene->GetBackGround());
		if(ImGui::Button("Select Monsters"))
			EditorHelper::Get()->SelectActor(context->GetSubsystem<MonsterManager>()->GetMonsters()[tmp_index]);
		if (ImGui::Button("Select ActorForSkill"))
			EditorHelper::Get()->SelectActor(context->GetSubsystem<MonsterManager>()->GetEffects(MonsterEffectType::Skill_Effect)[tmp_index]);
		if (ImGui::Button("Select LevelUp"))
			EditorHelper::Get()->SelectActor(context->GetSubsystem<MonsterManager>()->GetEffects(MonsterEffectType::LevelUp)[tmp_index]);
		if (ImGui::Button("Select Dropped"))
			EditorHelper::Get()->SelectActor(context->GetSubsystem<MonsterManager>()->GetEffects(MonsterEffectType::Dropped_Item)[tmp_index]);


		if (ImGui::Button("Add Actor"))
		{
			FileSystem::OpenFileDialog
			(
				[this](std::string str) {
					Actor* selectedActor = EditorHelper::Get()->GetSelectedActor();
					Vector3 position = !selectedActor ? Vector3(0, 0, 0) : selectedActor->GetComponent<Transform>() ? selectedActor->GetComponent<Transform>()->GetPosition() : Vector3(0, 0, 0);
					context->GetSubsystem<SceneManager>()->GetCurrentScene()->AddActor(str, position);
				},
				"(*.*);*.*",
					"../../_Assets/Scene/Mobs/"
			);
		}
		if (ImGui::Button("Save Actor"))
		{
			Actor* selectedActor = EditorHelper::Get()->GetSelectedActor();
			selectedActor->SaveToFile("../../_Assets/Scene/Mobs/" + selectedActor->GetName() + ".actor");
		}

		ImGui::PushItemWidth(100.0f);

		{
			Data_Field* fieldData = scene->GetDataField();

			std::string fieldDataName = fieldData ? fieldData->GetName() : "N\A";
			ImGui::InputText("Field Data -> ", &fieldDataName[0], fieldDataName.size(), ImGuiInputTextFlags_ReadOnly);

			if (ImGui::Button("Load Field Data"))
			{
				DataManager* dataManager = context->GetSubsystem<DataManager>();
				FileSystem::OpenFileDialog
				(
					[scene, dataManager](std::string str) { 
						scene->SetDataField(dataManager->GetData<Data_Field>(FileSystem::GetIntactFileNameFromPath(str)));
					},
					"(.data);.data;",
					"../../_Assets/Data/"
				);
				// map data 동기화 하자
			}
			std::string path = fieldData ? fieldData->GetBackGroundPath() : "N\A";
			ImGui::InputText("BackGroundPath", &path[0], path.size(), ImGuiInputTextFlags_ReadOnly);

			if (ImGui::Button("Load Background Image"))
			{
				FileSystem::OpenFileDialog
				(
					[fieldData](std::string str) {
						if(fieldData)
							fieldData->SetBackGroundPath(FileSystem::GetDirectoryLeft(str, "../../_Assets/Texture/"));
					},
					"(*.*);*.*;",
						"../../_Assets/Texture/"
				);
			}
		}
	}
}

void Widget_Inspector::ShowActor(Actor* actor)
{
	if (!actor)
		return;

	if (ImGui::CollapsingHeader("Actor", ImGuiTreeNodeFlags_DefaultOpen)) {
		std::string name = actor->GetName();
		bool isActive = actor->IsActive();
		bool isCameraAttached = actor->IsCameraAttached();

		ImGui::InputText("Actor Name", &name);

		ImGui::Checkbox("IsActive", &isActive);

		ImGui::Checkbox("IsCameraAttacted", &isCameraAttached);

		if (name != actor->GetName()) actor->SetName(name);
		if (isActive != actor->IsActive()) actor->SetActive(isActive);
		if (isCameraAttached != actor->IsCameraAttached())
		{
			actor->SetIsCameraAttached(isCameraAttached);
			if (isCameraAttached)
				context->GetSubsystem<SceneManager>()->GetCurrentScene()->GetCamera()->SetTransform(actor->GetComponent<Transform>());

		}
	}
}

void Widget_Inspector::ShowTransform(Transform * transform)
{
	if (!transform)
		return;

	Vector3 scale = transform->GetScale();
	Vector3 rotation = Math::QuaternionToEuler(transform->GetRotation());
	Vector3 position = transform->GetPosition();

	auto ShowFloat = [](const char* label, float* value, float min, float max) {
		ImGui::PushItemWidth(100.0f);
		ImGui::DragFloat(label, value, 0.5f, min, max);
		ImGui::PopItemWidth();
	};

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::Text("Pos");
		ImGui::SameLine(); ShowFloat("##posX", &position.x, -100000.0f, 100000.0f);
		ImGui::SameLine(); ShowFloat("##posY", &position.y, -100000.0f, 100000.0f);
		ImGui::SameLine(); ShowFloat("##posZ", &position.z, -100000.0f, 100000.0f);

		ImGui::Text("Roc");
		ImGui::SameLine(); ShowFloat("##rotX", &rotation.x, -181.0f, 181.0f);
		ImGui::SameLine(); ShowFloat("##rotY", &rotation.y, -181.0f, 181.0f);
		ImGui::SameLine(); ShowFloat("##rotZ", &rotation.z, -181.0f, 181.0f);

		ImGui::Text("Scl");
		ImGui::SameLine(); ShowFloat("##sclX", &scale.x, 0.1f, 100000.0f);
		ImGui::SameLine(); ShowFloat("##sclY", &scale.y, 0.1f, 100000.0f);
		ImGui::SameLine(); ShowFloat("##sclZ", &scale.z, 0.1f, 100000.0f);
	}

	transform->SetPosition(position);
	transform->SetRotation(Math::EulerToQuaternion(rotation));
	transform->SetScale(scale);
}

void Widget_Inspector::ShowRenderable(Renderable * renderable)
{
	if (!renderable)
		return;
	
	Mesh* mesh = renderable->GetMesh();
	Material* material = renderable->GetMaterial();

	if (ImGui::CollapsingHeader("Renderable", ImGuiTreeNodeFlags_DefaultOpen))
	{
		const Texture* albedo_texture = renderable->GetTexture(TextureType::Albedo);
		const Texture* normal_texture = renderable->GetTexture(TextureType::Normal);
		const Texture* emissive_texture = renderable->GetTexture(TextureType::Emissive);

		ShowRenderableTextureSlot(renderable, albedo_texture, "Albedo", TextureType::Albedo);
		ShowRenderableTextureSlot(renderable, normal_texture, "Normal", TextureType::Normal);
		ShowRenderableTextureSlot(renderable, emissive_texture, "Emissive", TextureType::Emissive);

		ImGui::PushItemWidth(100.0f);

		std::string meshName = mesh ? mesh->GetResourceName() : NULL_STRING;
		std::string materialName = material ? material->GetResourceName() : NULL_STRING;

		ImGui::TextUnformatted("Mesh");
		ImGui::SameLine(70.0f);
		ImGui::InputText("##Mesh", &meshName[0], meshName.size(), ImGuiInputTextFlags_ReadOnly);
		if (ImGui::Button("Load Mesh"))
		{
			FileSystem::OpenFileDialog
			(
				[renderable, this](std::string str) { renderable->SetMesh(FileSystem::GetDirectoryLeft(str, "../../_Assets/Data/"), FileSystem::GetIntactFileNameFromPath(str));},
				".mesh",
				"../../_Assets/Mesh/"
			);
		}
		ImGui::SameLine();
		if (ImGui::Button("Save Mesh"))
		{
			ResourceManager* resourceManager = context->GetSubsystem<ResourceManager>();
			FileSystem::SaveFileDialog
			(
				[renderable, resourceManager, meshName](std::string str) { resourceManager->Save<Mesh>(FileSystem::GetDirectoryLeft(str, "../../_Assets/Mesh/"), meshName); },
				".mesh",
				"../../_Assets/Mesh/"
			);
		}

		if(mesh) mesh->SetResourceName(meshName);

		ImGui::TextUnformatted("Material");
		ImGui::SameLine(70.0f);
		ImGui::InputText("##Material", &materialName[0], materialName.size(), ImGuiInputTextFlags_ReadOnly);
		if (ImGui::Button("Load Maerial"))
		{
			FileSystem::OpenFileDialog
			(
				[renderable, this](std::string str) { renderable->SetMaterial(FileSystem::GetDirectoryLeft(str, "../../_Assets/Material/"), FileSystem::GetIntactFileNameFromPath(str)); },
				".material",
				"../../_Assets/Material/"
			);
		}
		ImGui::SameLine();
		if (ImGui::Button("Save Material"))
		{
			ResourceManager* resourceManager = context->GetSubsystem<ResourceManager>();
			FileSystem::SaveFileDialog
			(
				[renderable, resourceManager, materialName](std::string str) { resourceManager->Save<Material>(FileSystem::GetDirectoryLeft(str, "../../_Assets/Material/"), materialName); },
				".material",
				"../../_Assets/Material/"
			);
		}

		if(material) material->SetResourceName(materialName);

		ShowMaterialInRenderable(material);
	}
}

void Widget_Inspector::ShowAnimator(std::vector<Animator*> animators, Actor* actor)
{
	if (animators.size() < 1)
		return;

	if (ImGui::CollapsingHeader("Animator", ImGuiTreeNodeFlags_DefaultOpen))
	{
		static int i = 0;
		ImGui::DragInt("animators Index", &i);
		if (i >= animators.size())
			i = animators.size() - 1;

		Animator* animator = animators[i];

		std::string name = "Animator Path is\n-> " + animator->GetAnimation()->GetResourcePath();
		ImGui::TextUnformatted(name.c_str());

		std::string dragged = DragAndDrop::GetDragAndDrop(ResourceType::Animation);
		if (FileSystem::GetExtensionFromPath(dragged) == ".anim" || FileSystem::GetExtensionFromPath(dragged) == ".txt")
			animator->SetAnimation(dragged, dragged, actor->GetComponent<Renderable>());

		if (ImGui::Button("Load Animation"))
		{
			ResourceManager* resourceManager = context->GetSubsystem<ResourceManager>();
			FileSystem::OpenFileDialog
			(
				[animator, actor](std::string str) { animator->SetAnimation(FileSystem::GetDirectoryLeft(str, "../../_Assets/Animation/"), FileSystem::GetFileNameFromPath(str), actor->GetComponent<Renderable>()); },
				".txt;.anim",
				"../../_Assets/Animation/"
			);
		}

		if (ImGui::Button("Reset Weight"))
		{
			if (animator) animator->ResetWeight();
		}

		if (ImGui::Button("Play"))
			animator->Play();

		if (ImGui::Button("Pause"))
			animator->Pause();

		if (ImGui::Button("Stop"))
			animator->Stop();
	}
}

void Widget_Inspector::ShowRigidBody(RigidBody* rigidBody)
{
	if (!rigidBody)
		return;

	RigidBodyType rigidBodyType = rigidBody->GetRigidBodyType();

	if (ImGui::CollapsingHeader("RigidBody", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (static_cast<int>(rigidBodyType) > stringsForRigidBodyType.size() || static_cast<int>(rigidBodyType) < 0)
			rigidBodyType = RigidBodyType::Character;

		const char* item_current = stringsForRigidBodyType[static_cast<int>(rigidBodyType)].c_str();
		if (ImGui::BeginCombo("RigidBody Type", item_current))
		{
			for (uint n = 0; n < static_cast<uint>(stringsForRigidBodyType.size()); n++)
			{
				bool is_selected = (item_current == stringsForRigidBodyType[n]);
				if (ImGui::Selectable(stringsForRigidBodyType[n].c_str(), is_selected))
				{
					item_current = stringsForRigidBodyType[n].c_str();
					rigidBodyType = static_cast<RigidBodyType>(n);
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus();			}
			ImGui::EndCombo();
		}

		if (rigidBodyType != rigidBody->GetRigidBodyType())
		{
			rigidBody->SetRigidBodyType(rigidBodyType);
			context->GetSubsystem<PhysicsManager>()->ChangeRigidBodyType(rigidBody, (int)rigidBodyType);
		}

		float mass = rigidBody->GetMass();
		float friction = rigidBody->GetFriction();
		Vector3 moveVector = rigidBody->GetMoveVector();
		Vector3 velocity = rigidBody->GetVelocity();
		Vector3 boundBox_center = rigidBody->GetBoundBox().GetCenter();
		Vector3 boundBox_size = rigidBody->GetBoundBox().GetSize();

		ImGui::TextUnformatted("mass");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat("##Mass", &mass, 0.01f, 0.01f,"%.3f", ImGuiInputTextFlags_CharsDecimal);

		ImGui::TextUnformatted("friction");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat("##Friction", &friction, 0.01f, 0.01f, "%.3f", ImGuiInputTextFlags_CharsDecimal);

		ImGui::InputFloat3("MoveVector", &moveVector.x, "%.3f", ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputFloat3("Velocity",   &velocity.x, "%.3f", ImGuiInputTextFlags_CharsDecimal);
		ImGui::InputFloat3("BoundBox Center", &boundBox_center.x, "%.3f");
		ImGui::InputFloat3("BoundBox Size", &boundBox_size.x, "%.3f");

		if (mass != rigidBody->GetMass()) rigidBody->SetMass(mass);
		if (friction != rigidBody->GetFriction()) rigidBody->SetFriction(friction);
		if (moveVector != rigidBody->GetMoveVector()) rigidBody->SetMoveVector(moveVector);
		if (velocity != rigidBody->GetVelocity())     rigidBody->SetVelocity(velocity);
		if (boundBox_center != rigidBody->GetBoundBox().GetCenter()) rigidBody->GetBoundBox().SetCenter(boundBox_center);
		if (boundBox_size != rigidBody->GetBoundBox().GetSize()) rigidBody->GetBoundBox().SetSize(boundBox_size);

		if(ImGui::Button("Reset RigidBody"))
		{
			rigidBody->GetBoundBox().Init(rigidBody->GetTransform());
			rigidBody->SetMoveVector(Vector3(0, 0, 0));
		}

	}
}

void Widget_Inspector::ShowScripter(Scripter* scripter, Actor* actor)
{
	if (!scripter)
		return;

	if (ImGui::CollapsingHeader("Scripter", ImGuiTreeNodeFlags_DefaultOpen))
	{
		std::string name = scripter->GetScript() ? "Script Path is\n-> " + scripter->GetScript()->GetResourcePath() : "No Script";
		ImGui::TextUnformatted(name.c_str());
		ImGui::SameLine();

		if (ImGui::Button("Load Script"))
		{
			ResourceManager* resourceManager = context->GetSubsystem<ResourceManager>();
			FileSystem::OpenFileDialog
			(
				[scripter, actor](std::string str) { scripter->SetScript(FileSystem::GetDirectoryLeft(str, "../../_Assets/Script/"), FileSystem::GetFileNameFromPath(str), actor); },
				"(.txt);.txt;",
				"../../_Assets/Script/"
			);
		}
	}
}

void Widget_Inspector::ShowController(Controller* controller)
{
	if (!controller)
		return;

	if (ImGui::CollapsingHeader("Controller", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool inInvicible = controller->IsInvincible();

		ImGui::Checkbox("Invincible", &inInvicible);

		std::string name = controller->GetMobData() ? "Data is \n-> " + controller->GetMobData()->GetName() : "No Data";
		ImGui::TextUnformatted(name.c_str());
		ImGui::SameLine();

		if (ImGui::Button("Load Mob Data"))
		{
			DataManager* dataManager = context->GetSubsystem<DataManager>();
			FileSystem::OpenFileDialog
			(
				[controller, dataManager](std::string str) { controller->SetMobData(dataManager->GetData<Data_Mob>(FileSystem::GetIntactFileNameFromPath(str))); },
				"(.data);.data;",
				"../../_Assets/Data/"
			);
		}
		ImGui::SameLine();

		if (ImGui::Button("Evolution"))
		{
			DataManager* dataManager = context->GetSubsystem<DataManager>();
			FileSystem::OpenFileDialog
			(
				[controller, dataManager](std::string str) { controller->Evolution(FileSystem::GetIntactFileNameFromPath(str)); },
				"(.data);.data;",
				"../../_Assets/Data/"
			);
		}
		ImGui::SameLine();
		if (ImGui::Button("Reset"))
			controller->SetMobData(nullptr);
		

		std::string attack1 = controller->GetAttack1Data() ? "Data is \n-> " + controller->GetAttack1Data()->GetName() : "No Data";
		ImGui::TextUnformatted(attack1.c_str());
		ImGui::SameLine();

		if (ImGui::Button("Load Attack1 Data"))
		{
			DataManager* dataManager = context->GetSubsystem<DataManager>();
			FileSystem::OpenFileDialog
			(
				[controller, dataManager](std::string str) { controller->SetAttack1Data(dataManager->GetData<Data_Skill>(FileSystem::GetIntactFileNameFromPath(str))); },
				"(.data);.data;",
				"../../_Assets/Data/"
			);
		}

		std::string attack2 = controller->GetAttack2Data() ? "Data is \n-> " + controller->GetAttack2Data()->GetName() : "No Data";
		ImGui::TextUnformatted(attack2.c_str());
		ImGui::SameLine();

		if (ImGui::Button("Load Attack2 Data"))
		{
			DataManager* dataManager = context->GetSubsystem<DataManager>();
			FileSystem::OpenFileDialog
			(
				[controller, dataManager](std::string str) { controller->SetAttack2Data(dataManager->GetData<Data_Skill>(FileSystem::GetIntactFileNameFromPath(str))); },
				"(.data);.data;",
				"../../_Assets/Data/"
			);
		}

		std::string guard = controller->GetGuardData() ? "Data is \n-> " + controller->GetGuardData()->GetName() : "No Data";
		ImGui::TextUnformatted(guard.c_str());
		ImGui::SameLine();

		if (ImGui::Button("Load Guard Data"))
		{
			DataManager* dataManager = context->GetSubsystem<DataManager>();
			FileSystem::OpenFileDialog
			(
				[controller, dataManager](std::string str) { controller->SetGuardData(dataManager->GetData<Data_Skill>(FileSystem::GetIntactFileNameFromPath(str))); },
				"(.data);.data;",
				"../../_Assets/Data/"
			);
		}

		std::string portal = controller->GetPortalData() ? "Data is \n-> " + controller->GetPortalData()->GetName() : "No Data";
		ImGui::TextUnformatted(portal.c_str());
		ImGui::SameLine();

		if (ImGui::Button("Load Portal Data"))
		{
			DataManager* dataManager = context->GetSubsystem<DataManager>();
			FileSystem::OpenFileDialog
			(
				[controller, dataManager](std::string str) { controller->SetPortalData(dataManager->GetData<Data_Portal>(FileSystem::GetIntactFileNameFromPath(str))); },
				"(.data);.data;",
				"../../_Assets/Data/"
			);
		}

		std::string dialog = controller->GetDialogData() ? "Data is \n-> " + controller->GetDialogData()->GetName() : "No Data";
		ImGui::TextUnformatted(dialog.c_str());
		ImGui::SameLine();

		if (ImGui::Button("Load Dialog Data"))
		{
			DataManager* dataManager = context->GetSubsystem<DataManager>();
			FileSystem::OpenFileDialog
			(
				[controller, dataManager](std::string str) { controller->SetDialogData(dataManager->GetData<Data_Dialog>(FileSystem::GetIntactFileNameFromPath(str))); },
				"(.data);.data;",
				"../../_Assets/Data/"
			);
		}
	}
}

void Widget_Inspector::ShowMaterialInRenderable(Material * material)
{
	if (!material)
		return;

	if (ImGui::TreeNodeEx("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		Vector2 tiling = material->GetUvTiling();
		Vector2 offset = material->GetUvOffset();
		float normalStrength = material->GetNormalStrength();
		Color4 albedoColor = material->GetAlbedoColor();
		SamplerType samplerType = material->GetSamplerType();

		ImGui::TextUnformatted("Tiling");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat2("##Tiling", &tiling.x, "%.3f", ImGuiInputTextFlags_CharsDecimal);
		
		ImGui::TextUnformatted("Offset");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat2("##Offset", &offset.x, "%.3f", ImGuiInputTextFlags_CharsDecimal);

		ImGui::TextUnformatted("NormalStrength");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat("##NormalStrength", &normalStrength, 0.0f, 0.1f, "%.3f", ImGuiInputTextFlags_CharsDecimal);

		ImGui::TextUnformatted("AlbedoColor");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat4("##AlbedoColor", &albedoColor.r, "%.3f", ImGuiInputTextFlags_CharsDecimal);

		ImGui::TextUnformatted("SamplerType");
		ImGui::SameLine(100.0f);

		static const char* item_current = stringsForSamplerCombobox[static_cast<int>(samplerType)].c_str();           
		if (ImGui::BeginCombo("SamplerType", item_current)) 
		{
			for (uint n = 0; n < static_cast<uint>(stringsForSamplerCombobox.size()); n++)
			{
				bool is_selected = (item_current == stringsForSamplerCombobox[n]);
				if (ImGui::Selectable(stringsForSamplerCombobox[n].c_str(), is_selected))
				{
					item_current = stringsForSamplerCombobox[n].c_str();
					samplerType = static_cast<SamplerType>(n);
				}
				if (is_selected)
					ImGui::SetItemDefaultFocus(); 
			}
			ImGui::EndCombo();
		}

		if (tiling != material->GetUvTiling()) material->SetUvTiling(tiling);
		if (offset != material->GetUvOffset()) material->SetUvOffset(offset);
		if (normalStrength != material->GetNormalStrength()) material->SetNormalStrength(normalStrength);
		if (albedoColor != material->GetAlbedoColor()) material->SetAlbedoColor(albedoColor);
		if (samplerType != material->GetSamplerType()) material->SetSamplerType(samplerType);

		ImGui::PopItemWidth();
		ImGui::TreePop();
	}
}

void Widget_Inspector::ShowRenderableTextureSlot(Renderable* renderable, const Texture * texture, const char * name, const TextureType & type)
{
	ImGui::TextUnformatted(name ? name : "N/A");
	ImGui::SameLine(100.0f);
	ImGui::Image(
		texture ? texture->GetShaderResourceView() : nullptr,
		ImVec2(80, 80),
		ImVec2(0, 0),
		ImVec2(1, 1),
		ImVec4(1, 1, 1, 1),
		ImColor(255, 255, 255, 255)
	);
	ImGui::SameLine();
	
	std::string dragged = DragAndDrop::GetDragAndDrop(ResourceType::Texture);
	if (FileSystem::IsSupportImageFile(dragged))
		renderable->SetTexture(type, dragged, dragged);

	if (ImGui::Button(("reset " + std::string(name)).c_str()))
		renderable->RemoveTexture(type);

}
