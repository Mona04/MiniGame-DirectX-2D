#pragma once
#include "../ISubsystem.h"
#include "Framework/Resource/IResource.h"

class ResourceManager final : public ISubsystem
{
public:
	ResourceManager(class Context* context);
	~ResourceManager();

	const bool Initialize() override;

	class ImageImporter* GetImageImporter() { return imageImporter; }
	class FontImporter* GetFontImporter() { return fontImporter; }

	template <typename T> T* Load(const std::string& path = NULL_STRING, const std::string& name = NULL_STRING);
	template <typename T> T* LoadUseThread(const std::string& path = NULL_STRING, const std::string& name = NULL_STRING);
	template <typename T> const bool Save(const std::string& path, const std::string& name);

	template <typename T> T* GetResourceFromName(const std::string& name);
	template <typename T> T* GetResourceFromPath(const std::string& path);
	template <typename T> const std::string GetResourceDirectory();

	void Clear_Temperate();
	void Set_TemperateMode(const bool& var) { this->bTemperateMode = var; }

private:
	void RegisterResource(class IResource* resource);
	void RegisterResourceDirectory
	(
		const ResourceType& type,
		const std::string& directory
	);

private:
	class ImageImporter* imageImporter;
	class FontImporter* fontImporter;

	typedef std::map<std::string, class IResource*> ResourceGroup;
	std::map<ResourceType, ResourceGroup> resourceGroups;
	std::map<ResourceType, ResourceGroup> resourceGroups_temperate;
	std::map<ResourceType, std::string> resourceDirectories;

	bool bTemperateMode = false;
};

template<typename T>
inline T* ResourceManager::Load(const std::string& path, const std::string& name)
{
	ResourceType type = IResource::DeduceResourceType<T>();
	T* resource = nullptr;

	if(type != ResourceType::Script)
		resource = GetResourceFromName<T>(name);

	if (!resource)
	{
		auto directory = resourceDirectories[type];

		resource = new T(context);
		resource->SetResourceType(type);
		resource->SetResourcePath(path);
		
		if (name != NULL_STRING)
			resource->SetResourceName(name);
		else
			resource->SetResourceName(FileSystem::GetIntactFileNameFromPath(path));

		if (FileSystem::IsExist(directory + path))
		{
			if (bTemperateMode && type == ResourceType::Texture)
				context->GetSubsystem<Thread>()->AddTask([resource, path, directory]() { resource->LoadFromFile(directory + path); });
			else
				resource->LoadFromFile(directory + path);
		}
		RegisterResource(resource);
	}

	return resource;
}

template<typename T>
inline T* ResourceManager::LoadUseThread(const std::string& path, const std::string& name)
{
	ResourceType type = IResource::DeduceResourceType<T>();
	T* resource = nullptr;

	if (type != ResourceType::Script)
		resource = GetResourceFromName<T>(name);

	if (!resource)
	{
		auto directory = resourceDirectories[type];

		resource = new T(context);
		resource->SetResourceType(type);
		resource->SetResourcePath(path);

		if (name != NULL_STRING)
			resource->SetResourceName(name);
		else
			resource->SetResourceName(FileSystem::GetIntactFileNameFromPath(path));

		if (FileSystem::IsExist(directory + path))
		{
			Thread* thread = context->GetSubsystem<Thread>();
			thread->AddTask([resource, path, directory]() {
				resource->LoadFromFile(directory + path);
			});
		}
		RegisterResource(resource);
	}

	return resource;
}

template<typename T>
inline const bool ResourceManager::Save(const std::string& path, const std::string& name)
{
	auto resource = GetResourceFromName<T>(name);
	if (!resource)
		return false;

	auto type = IResource::DeduceResourceType<T>();
	auto directory = resourceDirectories[type];

	resource->SaveToFile(directory + path);
	return true;
}

template<typename T>
inline T * ResourceManager::GetResourceFromName(const std::string & name)
{
	auto resources = resourceGroups[IResource::DeduceResourceType<T>()];
	auto result = resources.find(name);
	if ( result != resources.end())
		return static_cast<T*>(result->second);
	else
	{
		resources = resourceGroups_temperate[IResource::DeduceResourceType<T>()];
		result = resources.find(name);
		if (result != resources.end())
			return static_cast<T*>(result->second);
	}
	return nullptr;
}

template<typename T>
inline T * ResourceManager::GetResourceFromPath(const std::string & path)
{
	for (auto resource : resourceGroups[IResource::DeduceResourceType<T>()])
	{
		if (resource.second->GetResourcePath() == path)
			return static_cast<T*>(resource.second);
	}
	for (auto resource : resourceGroups_temperate[IResource::DeduceResourceType<T>()])
	{
		if (resource.second->GetResourcePath() == path)
			return static_cast<T*>(resource.second);
	}
	return nullptr;
}

template<typename T>
inline const std::string ResourceManager::GetResourceDirectory()
{
	return resourceDirectories[IResource::DeduceResourceType<T>()];
}
