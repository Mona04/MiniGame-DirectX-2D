#include "ResourceManager.h"
#include "FreeImage/ImageImporter.h"

ResourceManager::ResourceManager(class Context* context)
	: ISubsystem(context)
	, imageImporter(nullptr)
{
}

ResourceManager::~ResourceManager()
{
	SAFE_DELETE(imageImporter);
}

const bool ResourceManager::Initialize()
{
	imageImporter = new ImageImporter(context);

	return true;
}
