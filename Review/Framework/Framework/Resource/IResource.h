#pragma once
#include "Framework.h"

enum class ResourceType : uint
{
	Unknown,
	Mesh,
	Material,
	Texture,
	Animation,
	Audio,
	Font,
	Shader,
	Script
};

class IResource
{
private:
	friend class ResourceManager;

public:
	template <typename T>
	static ResourceType DeduceResourceType();

public:
	IResource(class Context* context)
		: context(context)
	{
		resourceManager = context->GetSubsystem<class ResourceManager>();
		id = GUIDGenerator::Generate();
	}
	virtual ~IResource() = default;

	const ResourceType& GetResourceType() const { return resourceType; }
	const std::string& GetResourceName() const { return resourceName; }
	const std::string& GetResourcePath() const { return resourcePath; }
	const uint& GetID() const { return id; }

	void SetResourceName(const std::string& name) { this->resourceName = name; }

protected:
	void SetResourceType(const ResourceType& type) { this->resourceType = type; }
	void SetResourcePath(const std::string& path) { this->resourcePath = path; }

	virtual void SaveToFile(const std::string& path) = 0;
	virtual void LoadFromFile(const std::string& path) = 0;

protected:
	class Context* context;
	class ResourceManager* resourceManager;

	ResourceType resourceType;
	std::string resourceName;
	std::string resourcePath;
	uint id;
};

template<typename T>
inline ResourceType IResource::DeduceResourceType()
{
	std::string type = typeid(T).name();

	ResourceType enumType = ResourceType::Unknown;
	if (type.find("Mesh") != std::string::npos)				enumType = ResourceType::Mesh;
	else if (type.find("Material") != std::string::npos)	enumType = ResourceType::Material;
	else if (type.find("Texture") != std::string::npos)		enumType = ResourceType::Texture;
	else if (type.find("Animation") != std::string::npos)	enumType = ResourceType::Animation;
	else if (type.find("Audio") != std::string::npos)		enumType = ResourceType::Audio;
	else if (type.find("Font") != std::string::npos)		enumType = ResourceType::Font;
	else if (type.find("Script") != std::string::npos)		enumType = ResourceType::Script;

	return enumType;
}
