#include "Framework.h"
#include "ResourceManager.h"
#include "Framework/Resource/Importer/ImageImporter.h"
#include "Framework/Resource/Importer/FontImporter.h"

ResourceManager::ResourceManager(Context * context)
	: ISubsystem(context)
	, imageImporter(nullptr)
	, fontImporter(nullptr)
{
}

ResourceManager::~ResourceManager()
{
	SAFE_DELETE(imageImporter);
	SAFE_DELETE(fontImporter);

	for (auto resourceGroup : resourceGroups)
	{
		for (auto resource : resourceGroup.second)
			SAFE_DELETE(resource.second);
	}
	resourceGroups.clear();

	for (auto resourceGroup : resourceGroups_temperate)
	{
		for (auto resource : resourceGroup.second)
			SAFE_DELETE(resource.second);
	}

	resourceDirectories.clear();
}

const bool ResourceManager::Initialize()
{
	imageImporter = new ImageImporter(context);
	fontImporter = new FontImporter(context);
	Glyphs glyphs;
	glyphs.fontSize = 25;
	glyphs.hintingType = HintingType::Light;
	glyphs.isForceAutoHint = false;
	glyphs.name = FONT_NANUM;
	glyphs.path = "../../_Assets/Font/NanumGothicBold.ttf";
	fontImporter->LoadFromFile(glyphs);

	RegisterResourceDirectory(ResourceType::Material, "../../_Assets/Material/");
	RegisterResourceDirectory(ResourceType::Mesh, "../../_Assets/Mesh/");
	RegisterResourceDirectory(ResourceType::Texture, "../../_Assets/Texture/");
	RegisterResourceDirectory(ResourceType::Audio, "../../_Assets/Audio/");
	RegisterResourceDirectory(ResourceType::Animation, "../../_Assets/Animation/");
	RegisterResourceDirectory(ResourceType::Font, "../../_Assets/Font/");
	RegisterResourceDirectory(ResourceType::Script, "../../_Assets/Script/");
	RegisterResourceDirectory(ResourceType::Audio, "../../_Assets/Audio/");

	return true;
}

void ResourceManager::Clear_Temperate()
{
	for (auto& map : resourceGroups_temperate)
	{
		for (auto& data : map.second)
			SAFE_DELETE(data.second);
		map.second.clear();
	}
	resourceGroups_temperate.clear();
}

void ResourceManager::RegisterResource(IResource * resource)
{
	if(bTemperateMode)
		resourceGroups_temperate[resource->GetResourceType()][resource->GetResourceName()] = resource;
	else
		resourceGroups[resource->GetResourceType()][resource->GetResourceName()] = resource;
}

void ResourceManager::RegisterResourceDirectory(const ResourceType & type, const std::string & directory)
{
	resourceDirectories[type] = directory;
}

// ================================


void ResourceManager::PlaySound(const std::string& path)
{
	AudioClip* src = Load<AudioClip>(path);
	if (!!src) src->Play();
}

