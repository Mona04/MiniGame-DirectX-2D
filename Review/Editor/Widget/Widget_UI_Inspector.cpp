#include "stdafx.h"
#include "Widget_UI_Inspector.h"
#include "./ImGui/Source/imgui.h"
#include "Framework/Core/Engine.h"

Widget_UI_Inspector::Widget_UI_Inspector(Context * context)
	: IWidget(context)
{
	title = "UI_Inspector";
	stringsForSamplerCombobox = { "clamp_point", "clamp_bilinear", "wrap_bilinear", "wrap_trilinear", "wrap_anisotropic" };
}

void Widget_UI_Inspector::Render()
{
	if (!bVisible)
		return;

	ShowUI(context->GetSubsystem<UIManager>()->GetCurrentUI());
}


void Widget_UI_Inspector::ShowUI(UI* ui)
{
	if (!ui)
		return;
	ShowRenderable(Engine::Get()->GetFrame()->GetRenderable());;

	if (ImGui::CollapsingHeader(ui->GetName().c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {

		auto component = EditorHelper::Get()->GetSelectedUIComponent();
		
		if (ImGui::Button("HPBar"))
		{
			component = context->GetSubsystem<MonsterManager>()->GetHP_Bar();
			EditorHelper::Get()->SelectUIComponent(component);
		}

		if (!component)
			return;

		if (ImGui::CollapsingHeader("Component", ImGuiTreeNodeFlags_DefaultOpen)) 
		{
			if(ImGui::Button("Load"))
			{
				const auto& uiManager = context->GetSubsystem<UIManager>();
				FileSystem::OpenFileDialog
				(
					[uiManager, &component](std::string str) { component->LoadFromFile(str); },
					".uicom",
					"../../_Assets/UI/"
				);
			}
			bool isVisible = component->GetIsVisible();
			ImGui::Checkbox("IsVisible", &isVisible);
			if (isVisible != component->GetIsVisible()) component->SetIsVisible(isVisible);

			std::string name = component->GetName();
			ImGui::InputText("Name", &name);
			if (name != component->GetName()) component->SetName(name);

			if (ImGui::Button("SetFront"))
			{
				auto type = component->GetType();

				switch (type)
				{
				case UIComponentType::Box: 	ui->GetComponents().emplace_back(ui->EraseComponent<Box>(component->GetName())); break;
				case UIComponentType::ProgressBar: ui->GetComponents().emplace_back(ui->EraseComponent<ProgressBar>(component->GetName())); break;
				case UIComponentType::Inventory:ui->GetComponents().emplace_back(ui->EraseComponent<Inventory>(component->GetName())); break;
				case UIComponentType::ToolTip: ui->GetComponents().emplace_back(ui->EraseComponent<ToolTip>(component->GetName())); break;
				case UIComponentType::SaveLoad: ui->GetComponents().emplace_back(ui->EraseComponent<SaveLoad>(component->GetName())); break;
				}
			}

			ShowExtra(component);

			static int j = 0;
			ImGui::DragInt("Frame Index", &j);
			if (j >= component->GetFrames().size())
				j = component->GetFrames().size() - 1;

			if (j < 0) return;

			const auto& frame = component->GetFrames()[j];
			{
				if (ImGui::CollapsingHeader("Frame", ImGuiTreeNodeFlags_DefaultOpen))
				{
					bool useDefaultCover = frame->UseDefaultCover();
					ImGui::Checkbox("useDefaultCover", &useDefaultCover);
					if (useDefaultCover != frame->UseDefaultCover()) frame->SetUseDefaultCover(useDefaultCover);
					ImGui::Text(("Frame Name is" + frame->GetName()).c_str());

					ShowRenderable(frame->GetRenderable());
					ShowTransform(frame->GetTransform());
					ShowAnimator(frame->GetAnimator(), frame);
					ShowScripter(frame->GetScripter(), frame);
				}
			}
		}
	}
}


void Widget_UI_Inspector::ShowExtra(IUIComponent* component)
{
	if (!component)
		return;
	if (ImGui::CollapsingHeader("Extra", ImGuiTreeNodeFlags_DefaultOpen))
	{
		UIComponentType type = component->GetType();
		switch (type)
		{
		case UIComponentType::ProgressBar:
		{
			ProgressBar* _component = static_cast<ProgressBar*>(component);
			Vector3 pos = _component->GetPosition();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat3("Pos", pos, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector3 scale = _component->GetScale();
			auto tmp = _component->GetScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat3("Scl", scale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			if (pos != _component->GetPosition()) _component->SetPosition(pos);
			if (scale != _component->GetScale()) _component->SetScale(scale);

			break;
		}
		case UIComponentType::Box:
			break;
		case UIComponentType::Text:
			break;
		case UIComponentType::Inventory:
		{
			Inventory* _component = static_cast<Inventory*>(component);

			if (ImGui::Button("Reset Inventory Slot"))
			{
				_component->Init_Default();
			}

			ImGui::InputInt("MaxX", &_component->GetMaxX());
			ImGui::InputInt("MaxY", &_component->GetMaxY());

			Vector3 pos = _component->GetPosition();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat3("Pos", pos, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 itmeScale = _component->GetItemScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("itmeScale", itmeScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 itemPadding = _component->GetItemPadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("itemPadding", itemPadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 tagScale = _component->GetTagScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("tagScale", tagScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 amountScale = _component->GetAmountScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("amountScale", amountScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 amountPadding = _component->GetAmountPadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("amountPadding", amountPadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			if (pos != _component->GetPosition()) _component->SetPosition(pos);
			if (itmeScale != _component->GetItemScale()) _component->SetItemScale(itmeScale);
			if (itemPadding != _component->GetItemPadding()) _component->SetItemPadding(itemPadding);
			if (tagScale != _component->GetTagScale()) _component->SetTagScale(tagScale);
			if (amountScale != _component->GetAmountScale()) _component->SetAmountScale(amountScale);
			if (amountPadding != _component->GetAmountPadding())_component->SetAmountPadding(amountPadding);
			break;
		}
		case UIComponentType::ToolTip:
		{
			ToolTip* _component = static_cast<ToolTip*>(component);
			Vector3 pos = _component->GetPosition();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat3("Pos", pos, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector3 scale = _component->GetScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat3("Scl", scale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			float width = _component->GetWidth();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat("width", &width, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();
			
			Vector2 titleScale = _component->GetTitleScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("titleScale", titleScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 titlePadding = _component->GetTitlePadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("titlePadding", titlePadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 tagScale = _component->GetTagScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("tagScale", tagScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 tagPadding = _component->GetTagPadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("tagPadding", tagPadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 infoScale = _component->GetInfoScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("infoScale", infoScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 infoPadding = _component->GetInfoPadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("infoPadding", infoPadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 slotPadding = _component->GetSlotPadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("slotPadding", slotPadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();
			

			if (pos != _component->GetPosition()) _component->SetPosition(pos);
			if (scale != _component->GetScale()) _component->SetScale(scale);
			if (width != _component->GetWidth()) _component->SetWidth(width);
			if (titleScale != _component->GetTitleScale()) _component->SetTitleScale(titleScale);
			if (titlePadding != _component->GetTitlePadding()) _component->SetTitlePadding(titlePadding);
			if (tagScale != _component->GetTagScale()) _component->SetTagScale(tagScale);
			if (tagPadding != _component->GetTagPadding()) _component->SetTagPadding(tagPadding);
			if (infoScale != _component->GetInfoScale()) _component->SetInfoScale(infoScale);
			if (infoPadding != _component->GetInfoPadding()) _component->SetInfoPadding(infoPadding);
			if (slotPadding != _component->GetSlotPadding()) _component->SetSlotPadding(slotPadding);

			break;
		}
		case UIComponentType::Evolution:
		{
			Evolution* _component = static_cast<Evolution*>(component);

			if (ImGui::Button("Reset Evolution Slot"))
			{
				_component->Init_Default();
			}

			Vector3 pos = _component->GetPosition();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat3("Pos", pos, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 tagScale = _component->GetTagScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("tagScale", tagScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 itemScale = _component->GetItemScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("itemScale", itemScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 itemPadding = _component->GetItemPadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("itemPadding", itemPadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 infoPadding = _component->GetInfoPadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("infoPadding", infoPadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 infoScale = _component->GetInfoScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("infoScale", infoScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector3 tipPosition = _component->GetTipPosition();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat3("tipPosition", tipPosition, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 tipScale = _component->GetTipScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("tipScale", tipScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();


			if (pos != _component->GetPosition()) _component->SetPosition(pos);
			if (tagScale != _component->GetTagScale()) _component->SetTagScale(tagScale);
			if (itemScale != _component->GetItemScale()) _component->SetItemScale(itemScale);
			if (itemPadding != _component->GetItemPadding()) _component->SetItemPadding(itemPadding);
			if (infoScale != _component->GetInfoScale()) _component->SetInfoScale(infoScale);
			if (infoPadding != _component->GetInfoPadding())_component->SetInfoPadding(infoPadding);
			if (tipScale != _component->GetTipScale()) _component->SetTipScale(tipScale);
			if (tipPosition != _component->GetTipPosition())_component->SetTipPosition(tipPosition);
			break;
		}
		case UIComponentType::SaveLoad:
		{
			SaveLoad* _component = static_cast<SaveLoad*>(component);

			Vector3 pos = _component->GetPosition();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat3("Pos", pos, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 tagScale = _component->GetTagScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("tagScale", tagScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 itemScale = _component->GetItemScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("itemScale", itemScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 itemPadding = _component->GetItemPadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("itemPadding", itemPadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 infoPadding = _component->GetInfoPadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("infoPadding", infoPadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 infoScale = _component->GetInfoScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("infoScale", infoScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			if (pos != _component->GetPosition()) _component->SetPosition(pos);
			if (tagScale != _component->GetTagScale()) _component->SetTagScale(tagScale);
			if (itemScale != _component->GetItemScale()) _component->SetItemScale(itemScale);
			if (itemPadding != _component->GetItemPadding()) _component->SetItemPadding(itemPadding);
			if (infoScale != _component->GetInfoScale()) _component->SetInfoScale(infoScale);
			if (infoPadding != _component->GetInfoPadding())_component->SetInfoPadding(infoPadding);
			break;
		}
		case UIComponentType::VerticalList:
		{
			VerticalList* _component = static_cast<VerticalList*>(component);

			Vector3 pos = _component->GetPosition();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat3("Pos", pos, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 itemScale = _component->GetItemScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("itemScale", itemScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 itemPadding = _component->GetItemPadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("itemPadding", itemPadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 infoPadding = _component->GetInfoPadding();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("infoPadding", infoPadding, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			Vector2 infoScale = _component->GetInfoScale();
			ImGui::PushItemWidth(100.0f);
			ImGui::DragFloat2("infoScale", infoScale, 0.001f, -100.f, 100.f);
			ImGui::PopItemWidth();

			if (pos != _component->GetPosition()) _component->SetPosition(pos);
			if (itemScale != _component->GetItemScale()) _component->SetItemScale(itemScale);
			if (itemPadding != _component->GetItemPadding()) _component->SetItemPadding(itemPadding);
			if (infoScale != _component->GetInfoScale()) _component->SetInfoScale(infoScale);
			if (infoPadding != _component->GetInfoPadding())_component->SetInfoPadding(infoPadding);
			break;
		}

		}
	}
}

void Widget_UI_Inspector::ShowTransform(Transform * transform)
{
	if (!transform)
		return;

	Vector3 scale = transform->GetScale();
	Vector3 position = transform->GetPosition();

	auto ShowFloat = [](const std::string& str, float* value, float min, float max) {
		ImGui::PushItemWidth(100.0f);
		ImGui::DragFloat(str.c_str(), value, 0.001f, min, max);
		ImGui::PopItemWidth();
	};

	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::Text("Pos");
		ImGui::SameLine(); ShowFloat("##posX", &position.x, -1000.0f, 1000.0f);
		ImGui::SameLine(); ShowFloat("##posY", &position.y, -1000.0f, 1000.0f);
		ImGui::SameLine(); ShowFloat("##posZ", &position.z, -1000.0f, 1000.0f);

		ImGui::Text("Scl");
		ImGui::SameLine(); ShowFloat("##sclX", &scale.x, 0.0001f, 100.0f);
		ImGui::SameLine(); ShowFloat("##sclY", &scale.y, 0.0001f, 100.0f);
		ImGui::SameLine(); ShowFloat("##sclZ", &scale.z, 0.0001f, 100.0f);
	}

	transform->SetPosition(position);
	transform->SetScale(scale);
}

void Widget_UI_Inspector::ShowRenderable(Renderable * renderable)
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
				[renderable, this](std::string str) { renderable->SetMesh(FileSystem::GetDirectoryLeft(str, "../../_Assets/Mesh/"), FileSystem::GetIntactFileNameFromPath(str)); },
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

		if (mesh) mesh->SetResourceName(meshName);

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

		if (material) material->SetResourceName(materialName);

		ShowMaterialInRenderable(material);
	}
}

void Widget_UI_Inspector::ShowAnimator(Animator* animator, class UI_Component_Frame* frame)
{
	if (!animator)
		return;

	if (ImGui::CollapsingHeader("Animator", ImGuiTreeNodeFlags_DefaultOpen))
	{
		std::string name = "Animator Path is\n-> " + (animator->GetAnimation() ? animator->GetAnimation()->GetResourcePath() : "N\A");
		ImGui::TextUnformatted(name.c_str());

		std::string dragged = DragAndDrop::GetDragAndDrop(ResourceType::Animation);
		if (FileSystem::GetExtensionFromPath(dragged) == ".anim" || FileSystem::GetExtensionFromPath(dragged) == ".txt")
			animator->SetAnimation(dragged, dragged, frame->GetRenderable());

		if (ImGui::Button("Load Animation"))
		{
			ResourceManager* resourceManager = context->GetSubsystem<ResourceManager>();
			FileSystem::OpenFileDialog
			(
				[animator, frame](std::string str) { animator->SetAnimation(FileSystem::GetDirectoryLeft(str, "../../_Assets/Animation/"), FileSystem::GetFileNameFromPath(str), frame->GetRenderable()); },
				".txt;.anim",
				"../../_Assets/Animation/"
			);
		}

		if (ImGui::Button("Play"))
			animator->Play();

		if (ImGui::Button("Pause"))
			animator->Pause();

		if (ImGui::Button("Stop"))
			animator->Stop();
	}
}

void Widget_UI_Inspector::ShowScripter(Scripter* scripter, UI_Component_Frame* frame)
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
				[scripter, frame](std::string str) { scripter->SetScript(FileSystem::GetDirectoryLeft(str, "../../_Assets/Script/"), FileSystem::GetFileNameFromPath(str), frame); },
				"(.txt);.txt;",
				"../../_Assets/Script/"
			);
		}

		if (ImGui::Button("Set Null"))
		{
			ResourceManager* resourceManager = context->GetSubsystem<ResourceManager>();
			scripter->SetScript();
		}
	}
}

void Widget_UI_Inspector::ShowMaterialInRenderable(Material * material)
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
		ImGui::InputFloat2("##Tiling", &tiling[0], "%.3f", ImGuiInputTextFlags_CharsDecimal);

		ImGui::TextUnformatted("Offset");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat2("##Offset", &offset[0], "%.3f", ImGuiInputTextFlags_CharsDecimal);

		ImGui::TextUnformatted("NormalStrength");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat("##NormalStrength", &normalStrength, 0.0f, 0.1f, "%.3f", ImGuiInputTextFlags_CharsDecimal);

		ImGui::TextUnformatted("AlbedoColor");
		ImGui::SameLine(100.0f);
		ImGui::InputFloat4("##AlbedoColor", &albedoColor[0], "%.3f", ImGuiInputTextFlags_CharsDecimal);

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

void Widget_UI_Inspector::ShowRenderableTextureSlot(Renderable* renderable, const Texture * texture, const char * name, const TextureType & type)
{
	ImGui::PushID(name); // material id 공유? 같은 material 이야 ㅄ새끼야 그래 나말이야 
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

		std::string dragged = DragAndDrop::GetDragAndDrop(ResourceType::Texture);

		if (FileSystem::IsSupportImageFile(dragged))
			renderable->SetTexture(type, dragged, FileSystem::GetIntactFileNameFromPath(dragged));

		ImGui::SameLine();
		if (ImGui::Button("Reset"))
			renderable->SetTexture(type, NULL_STRING, NULL_STRING);
	}
	ImGui::PopID();
}
