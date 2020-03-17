#include "stdafx.h"
#include "IconProvider.h"
#include "Framework/Resource/Texture.h"

void IconProvider::Initialize(Context * context)
{
	this->context = context;
	this->resourceManager = context->GetSubsystem<ResourceManager>();

	Load("../../_Assets/Texture/Icon/folder.png", IconType::Thumbnail_Folder);
	Load("../../_Assets/Texture/Icon/file.png", IconType::Thumbnail_File);
	Load("../../_Assets/Texture/Icon/playButton.png", IconType::Button_Play);
	Load("../../_Assets/Texture/Icon/stopButton.png", IconType::Button_Stop);
	Load("../../_Assets/Texture/Icon/pauseButton.png", IconType::Button_Pause);
	Load("../../_Assets/Texture/Icon/log_info.png", IconType::Button_Info);
	Load("../../_Assets/Texture/Icon/log_warning.png", IconType::Button_Warning);
	Load("../../_Assets/Texture/Icon/log_error.png", IconType::Button_Error);
}

Thumbnail * IconProvider::Load(const std::string & path, const IconType & type)
{
	Thumbnail* result;

	if (type != IconType::Custom)
	{
		result = GetThumbnailFromType(type);
		if (result)
			return result;
	}
	else
	{
		result = GetThumbnailFromPath(path);
		if (result)
			return result;
	}

	if (FileSystem::IsFolder(path)) {
		Texture* texture = resourceManager->LoadUseThread<Texture>("/Icon/folder.png", "Folder Icon");
		texture->SetMipChained(false);
		resourceManager->LoadUseThread<Texture>("/Icon/folder.png", "Folder Icon");
		return &thumbnails.emplace_back(IconType::Thumbnail_Folder, texture, path);
	}

	if (FileSystem::IsSupportImageFile(path)){
		Texture* texture = resourceManager->LoadUseThread<Texture>(path, path);
		texture->SetMipChained(false);
		resourceManager->LoadUseThread<Texture>(path, path);

		return &thumbnails.emplace_back(Thumbnail(type, texture, path));
	}

	return GetThumbnailFromType(IconType::Thumbnail_File);
}

auto IconProvider::GetShaderResourceFromType(const IconType & type) -> ID3D11ShaderResourceView *
{
	return Load("", type)->texture->GetShaderResourceView();
}

auto IconProvider::GetShaderResourceFromPath(const std::string & path) -> ID3D11ShaderResourceView *
{
	return Load(path)->texture->GetShaderResourceView();
}

auto IconProvider::ImageButton(const Thumbnail & thumbnail, const ImVec2 & size) -> const bool
{
	ImGui::PushID(thumbnail.path.c_str());
	bool bPressed = ImGui::ImageButton
	(
		thumbnail.texture->GetShaderResourceView(),
		size
	);
	ImGui::PopID();
	return bPressed;
}

auto IconProvider::ImageButton(const IconType & type, const ImVec2 & size) -> const bool
{
	bool bPressed = ImGui::ImageButton
	(
		GetShaderResourceFromType(type),
		size
	);
	return bPressed;
}

auto IconProvider::ImageButton(const std::string & path, const ImVec2 & size) -> const bool
{
	bool bPressed = ImGui::ImageButton
	(
		GetShaderResourceFromPath(path),
		size
	);
	return bPressed;
}

auto IconProvider::GetThumbnailFromType(const IconType & type) -> Thumbnail *
{
	for (auto& thumbnail : thumbnails)
	{
		if (thumbnail.type == type)
			return &thumbnail;
	}
	return nullptr;
}

auto IconProvider::GetThumbnailFromPath(const std::string & path) -> Thumbnail *
{
	for (auto& thumbnail : thumbnails)
	{
		if (thumbnail.path == path)
			return &thumbnail;
	}
	return nullptr;
}
